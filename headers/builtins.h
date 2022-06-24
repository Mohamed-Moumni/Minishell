/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:04:25 by mmoumni           #+#    #+#             */
/*   Updated: 2022/06/24 17:09:21 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
#define BUILTINS_H

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}t_envp;

void	echo(char ** str);
void	ft_pwd(t_envp *envp_list);
int		ft_unset(t_envp *envp, char *env_to_unset);
void	ft_cd(t_envp *envp, const char *str);
int		is_nl_valid(char *str);
void	ft_print(char **str, int condition);
t_envp	*creat_node(char *str);
void	envp_add_back(t_envp **envp_list, t_envp *node);
t_envp	*envp_to_list(char **envp);
t_envp	*search_key(t_envp *envp_list, char *key);

#endif