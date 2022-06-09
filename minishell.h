/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-iaz <yait-iaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:48:02 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/06/09 13:07:28 by yait-iaz         ###   ########.fr       */
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

typedef struct s_grammar
{
	int 				n;
	e_token				token;
	struct s_grammar	*prev;
	struct s_grammar	*next;
	
}				t_grammar;

int		ft_strlen(char *str);
char	*ft_strchr(char *s, int c);
int		ft_strcmp(char *s1, char *s2);
int		advanced_strlen(char *start, char *end);
char	*ft_substr(char *s, int start, int len);
char	*ft_strdupi(const char *s1, int l);
char	*ft_strjoin(char *s1, char *s2);

#endif