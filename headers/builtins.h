/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:04:25 by mmoumni           #+#    #+#             */
/*   Updated: 2022/06/28 09:39:11 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
#define BUILTINS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <paths.h>

# define EXPORT_KEY "declare -x "

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}t_envp;

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

void		echo(char ** str);
void		ft_pwd(t_envp *envp_list);
int			ft_unset(t_envp *env, char *key);
char		*ft_cd_home(char *path);
int			ft_cd(t_envp *env, char *path);
int			is_nl_valid(char *str);
void		ft_print(char **str, int condition);
t_envp		*creat_node(char *str);
void		envp_add_back(t_envp **envp_list, t_envp *node);
t_envp		*envp_to_list(char **envp);
t_envp		*search_key(t_envp *envp_list, char *key);
void		export_add_back(t_export **export, t_export *new);
char		*ft_append_exp_key(char *str);
char		*ft_append_dqoute(char *str);
t_export	*env_to_expo_list(char **env);
t_export	*export_node(char *key, char *value);
t_export	*last_expo(t_export *export);
void		ft_swap(t_envp *a, t_envp *b);
char		*cmd_valid(char *cmd);
char		**std_paths(char *str);
int			check_absolut_path(char *cmd);
t_envp		*ft_list_last(t_envp *env_list);

#endif