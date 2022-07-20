/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 08:45:50 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/20 15:44:31 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/struct.h"
#include "../headers/minishell.h"
#include "../headers/builtins.h"

t_envp	*creat_node(char *str)
{
	t_envp	*node;
	char	**splited;
	char	*value_node;

	splited = NULL;
	value_node = NULL;
	node = (t_envp *)malloc(sizeof(t_envp));
	if (!node)
		return (NULL);
	splited = ft_split(str, '=');
	node->key = splited[0];
	if (splited[1] == NULL || !ft_strcmp(splited[0], "OLDPWD"))
	{
		free(splited[1]);
		value_node = (char *)malloc(sizeof(char));
		value_node[0] = '\0';
		node->value = value_node;
	}
	else
		node->value = splited[1];
	free(splited);
	node->next = NULL;
	return (node);
}

void	envp_add_back(t_envp **envp_list, t_envp *node)
{
	t_envp	*temp_envp;

	if (*envp_list == NULL)
		*envp_list = node;
	else
	{
		temp_envp = ft_list_last(*envp_list);
		temp_envp->next = node;
	}
}

t_envp	*envp_to_list(char **envp)
{
	int		i;
	t_envp	*envp_list;
	char	*pwd;
	char	*shlvl;

	i = 0;
	envp_list = NULL;
	pwd = NULL;
	if (!(*envp))
		envp_list = without_env();
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "SHLVL", 5))
		{
			shlvl = ft_strjoin_ad("SHLVL=", \
			ft_itoa(ft_atoi(&envp[i][6]) + 1), 2);
			envp_add_back(&envp_list, \
			creat_node(shlvl));
			// free (shlvl);
		}
		else
			envp_add_back(&envp_list, creat_node(envp[i]));
		i++;
	}
	return (free(shlvl),envp_list);
}

char	**list_to_envp(t_envp *env_list)
{
	char			**env_tab;
	t_envp			*temp;
	unsigned int	i;

	temp = env_list;
	i = 0;
	env_tab = (char **)malloc(sizeof(char *) * (t_envp_size(env_list) + 1));
	if (!env_tab)
		return (NULL);
	while (temp)
	{
		env_tab[i] = ft_strjoin(temp->key, "=");
		env_tab[i] = ft_strjoin(env_tab[i], temp->value);
		i++;
		temp = temp->next;
	}
	env_tab[i] = NULL;
	return (env_tab);
}
