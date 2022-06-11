/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-iaz <yait-iaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:48:02 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/06/10 18:16:57 by yait-iaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum token
{
	PIPE,			// |
	OPTION,			// -
	SINGLE_QUOTE,	// '
	DOUBLE_QUOTE,	// "
	OPERATOR,		// < << $ >> >
	UNCHECKED,
}			e_token;

typedef struct s_lexer
{
	int 				n;
	e_token				token;
	struct s_lexer	*prev;
	struct s_lexer	*next;
	
}				t_lexer;

int		ft_strlen(char *str);
char	*ft_strchr(char *s, int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		advanced_strlen(char *start, char *end);
char	*ft_substr(char *s, int start, int len);
char	*ft_strdupi(const char *s1, int l);
char	*ft_strjoin(char *s1, char *s2);

char	*single_quote(char **word, char *line, char *quote);
char	*double_quote(char **word, char *line, char *quote);
char	*add_before_quote(char *quote, char *line);
char	*quote_handle(char **word, char *line, char *start);

#endif