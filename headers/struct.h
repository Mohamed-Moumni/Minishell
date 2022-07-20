/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 22:28:27 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/07/20 13:11:17 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

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
# include <limits.h>
# include <errno.h>
# include <dirent.h>
# define BUFFER_SIZE 1
# define SHLVL "SHLVL=1"
# define USRBINENV  "_=./minishell"
# define EXPORT_KEY "declare -x "
# define OLDPWD "OLDPWD"
# define MAX "2147483647"
# define MIN "2147483648"

typedef struct s_update
{
	int				exit_status;
	int				old_pwd;
	int				unset_path;
	int				herdoc;
}	t_upd;

t_upd	g_minishell;

typedef enum e_token
{
	WORD,				
	OPTION,				
	SINGLE_QUOTE,		
	DOUBLE_QUOTE,		
	PIPE,				
	RIGHT_REDIR,		
	DOUBLE_RIGHT_REDIR,	
	LEFT_REDIR,			
	HEREDOC,			
	UNCHECKED,			
	FILENAME
}	t_token;

typedef struct s_lexer
{
	char			*content;
	t_token			token;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}			t_lexer;

typedef struct s_char
{
	char			*argv;
	struct s_char	*next;
}				t_char;

typedef struct s_cmds
{
	t_token			type;
	t_char			*argv;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}			t_cmds;

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}			t_envp;

#endif