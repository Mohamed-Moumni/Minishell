/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-iaz <yait-iaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:04:25 by mmoumni           #+#    #+#             */
/*   Updated: 2022/06/27 14:09:15 by yait-iaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
#define BUILTINS_H

#include "minishell.h"

#define EXPORT_KEY "declare -x "

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
t_envp		*ft_list_last(t_envp *env_list);

#endif