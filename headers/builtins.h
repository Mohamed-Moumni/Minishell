/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:04:25 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/02 20:20:12 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
#define BUILTINS_H

#include "../headers/struct.h"

void		ft_echo(char ** str);
void		ft_pwd(char **argv);
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
char        *ft_append_exp_key(char *str, int *opwd_check);
char        *ft_append_dqoute(char *str, int *opwd_check);
t_export	*env_to_expo_list(char **env);
t_export	*export_node(char *key, char *value);
t_export	*last_expo(t_export *export);
void		ft_swap(t_export *a, t_export *b);
char		*cmd_valid(char *cmd);
char		**std_paths(char *str);
int			check_absolut_path(char *cmd);
t_envp		*ft_list_last(t_envp *env_list);
void	ft_export(t_export *export, t_char *args);
t_envp      *without_env(void);
void        ft_env(char **envp, char **env);
t_export	*search_exportkey(t_export *export, char *key);
char        *ft_strstr(char *str, char *to_find);
#endif