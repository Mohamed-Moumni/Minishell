/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:04:25 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/17 12:31:07 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
#define BUILTINS_H

#include "../headers/struct.h"
#include "../headers/minishell.h"

int				is_nl_valid(char *str);
void			ft_print(char **str, int condition);
void			ft_echo(char ** str);
void			ft_pwd(char **argv);
char			*ft_cd_home(char *path);
int				ft_cd(t_envp **env, t_char *path);
t_envp			*without_env(void);
t_envp			*creat_node(char *str);
void			envp_add_back(t_envp **envp_list, t_envp *node);
t_envp			*envp_to_list(char **envp);
t_envp			*search_key(t_envp *envp_list, char *key);
unsigned int	t_envp_size(t_envp *env_list);
char			**list_to_envp(t_envp *env_list);
void			ft_env(t_envp *env, t_char *args);
void			env_sort(t_envp *env);
void			ft_swap(t_envp *a, t_envp *b);
void			ft_export(t_envp **env, t_char *args);
void			add_export_vars(t_envp **env, t_char *args);
void			trait_arg(t_envp **env, t_char *arg);
void			get_key_value(char *str, char **key, char **value, int cond);
int				valid_arg(char *str);
void            ft_unset(t_envp **env, t_char *args);
void			delete_node(t_envp **env, t_char *arg);
int				valid_unset(char *str);
char            **list_to_envp(t_envp *env_list);
// void            is_builtin(t_cmds *cmd, t_envp **env, int *res);
void            run_builtin(t_cmds *cmd, t_envp **env);
void            is_builtin(t_cmds *cmd, int *res);
t_envp          *delete_head(t_envp *head);
void            ft_split_key_val(char *str, char c, char **key, char **value);
#endif