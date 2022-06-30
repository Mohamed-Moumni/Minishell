/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-iaz <yait-iaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 22:28:27 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/06/29 22:30:06 by yait-iaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <paths.h>
# include <sys/types.h>
# include <sys/uio.h>

# define BUFFER_SIZE 1

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
	HEREDOC,			//			8
	UNCHECKED,			//			9
	FILENAME			//			10
}			e_token;

typedef struct s_lexer
{
	char			*content;
	e_token			token;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}			t_lexer;


typedef struct s_char
{
	char 			*argv;
	struct s_char	*next;
}				t_char;

typedef struct s_cmds
{
	e_token			type;
	t_char			*argv;
	int				fd[2];
	struct s_cmds	*next;
	struct s_cmds	*prev;
}			t_cmds;
# define EXPORT_KEY "declare -x "

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}			t_envp;

typedef struct s_export
{
	char	*key;
	char	*value;
	struct s_export *next;
}t_export;

typedef struct s_history
{
	char				*hist;
	struct s_history	*next;
}t_hist;

#endif