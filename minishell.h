/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:48:02 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/06/13 10:01:21 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_token
{
	WORD,			// SIMPLE WORD	0
	PIPE,			// |			1
	OPTION,			// -			2
	SINGLE_QUOTE,	// '			3
	DOUBLE_QUOTE,	// "			4
	OPERATOR,		// < << >> >	5
	RIGHT_OPER,
	LEFT_OPER,
	RRIGHT_OPER,
	LLEFT_OPER,
	FILENAME,
	CMD,
	PATHNAME
}			e_token;

typedef struct s_lexer
{
	int				n;
	char			*content;
	e_token			token;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}				t_lexer;

// typedef enum e_node
// {
	
// }e_node;

typedef struct s_ast
{
	e_token			node_type;
	char			*value;
	struct s_ast	*left;
	struct s_ast	*right;
}t_ast;



int		ft_strlen(char *str);
char	*ft_strchr(char *s, int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		advanced_strlen(char *start, char *end);
char	*ft_substr(char *s, int start, int len);
char	*ft_strdupi(const char *s1, int l);
char	*ft_strjoin(char *s1, char *s2);

char	*single_quote(char **word, char *line, char *quote, char *first_q);
char	*double_quote(char **word, char *line, char *quote, char *first_q);
char	*add_before_quote(char *quote, char *line);
char	*quote_handle(char **word, char *line, char *start);

t_lexer	*get_lexer(char *line);
void	print_lexer(t_lexer *list);
void	add_node(t_lexer **list, char *word);
void	node_init(t_lexer **list, char *word);

void	remove_quote(char **word, char quote);
void	check_option(char *word, e_token *token);
void	check_term(char **word, e_token *token);
e_token	ft_tokenize(char **word);
t_ast	*execution(void);
t_ast	*command(void);
t_ast	*simple_command(void);
t_ast	*create_node(e_token nodetype, char *value, t_ast *left, t_ast *right);
void	next_token(void);
void	prev_token(void);
int		list_size(t_lexer *tokens);
void	exepect(void);
void	free_tree(t_ast *tree);
void	free_tokens(t_lexer *tokens);

#endif