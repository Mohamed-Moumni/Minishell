/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:48:02 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/06/17 17:53:47 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef enum e_token
{
	WORD,				//			0
	OPTION,				// -		1
	SINGLE_QUOTE,		// '		2
	DOUBLE_QUOTE,		// "		3
	PIPE,				// |		4
	RIGHT_REDIR,		//			5
	DOUBLE_RIGHT_REDIR,	//			6	
	LEFT_REDIR,			//			7
	DOUBLE_LEFT_REDIR,	//			8
	UNCHECKED,			//			9
	FILENAME			//			10
}			e_token;

typedef struct s_lexer
{
	char			*content;
	e_token			token;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}				t_lexer;

typedef struct s_ast
{
	e_token			node_type;
	char			*value;
	struct s_ast	*left;
	struct s_ast	*right;
}t_ast;

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}t_envp;

typedef struct s_history
{
	char				*histo;
	struct s_history	*next;
}t_hist;

// typedef struct	s_infos
// {
// 	t_ast	*ast;
// 	t_lexer *lexer
// }t_info;

int		ft_strlen(char *str);
char	*ft_strchr(char *s, int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		advanced_strlen(char *start, char *end);
char	*ft_substr(char *s, int start, int len);
char	*ft_strdupi(const char *s1, int l);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strrchr(char *s, int c);

char	*single_quote(char **word, char *line, char *quote, char *first_q);
char	*double_quote(char **word, char *line, char *quote, char *first_q);
char	*add_before_quote(char *quote, char *line);
char	*quote_handle(char **word, char *line, char *start);
int		between_quote(char *line, char *operator, char quote);
t_lexer	*get_lexer(char *line);
void	print_lexer(t_lexer *list);
int		create_node_lex(t_lexer **list, char *line, int *i, int *j);
void	add_node(t_lexer **list, char *word, e_token token);
void	node_init(t_lexer **list, char *word, e_token token);
int		check_last_node(t_lexer *list);
int		check_operator(char *line);
int		split_operator(t_lexer **list, char *line);
void	specify_operator(char *word, e_token *token);
void	free_list(t_lexer *list);
void	print_lexer(t_lexer *list);

void	remove_quote(char **word, char quote);
void	check_option(char *word, e_token *token);
void	check_term(char **word, e_token *token);
char	*split_redirection(t_lexer **list, char *word);
e_token	ft_tokenize(char **word);
t_ast	*create_node(e_token nodetype, char *value, t_ast *left, t_ast *right);
t_lexer	*next_token(t_lexer *tokens);
t_ast	*pipeline(t_lexer *lex);
t_ast	*command(t_lexer **lex);
void	free_tree(t_ast *tree);
void    display(t_ast *ast);

/* Buitlins Functions */

int		is_nl_valid(char *str);
void	ft_print(char **str, int condition);
void	echo(char ** str);
int		is_nl_valid(char *str);
void	ft_print(char **str, int condition);
char	**ft_split(char const *s, char c);
void	envp_add_back(t_envp **envp_list, t_envp *node);
t_envp	*envp_to_list(char **envp);
t_envp	*creat_node(char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
t_envp  *ft_list_last(t_envp *env_list);
t_envp	*search_key(t_envp *envp_list, char *key);
void	redirection(t_ast **tree, t_lexer **lex);

#endif