/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:53:42 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/03 15:42:58 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/struct.h"
#include "../headers/minishell.h"
#include "../headers/builtins.h"

int	is_nl_valid(char *str)
{
	int i;

	i = 1;
	if (str[0] == '-')
	{
		while (str[i] == 'n')
			i++;
		if (str[i] != '\0')
			return (1);
		return (0);
	}
	return (1);
}

void	ft_print(char **str, int condition)
{
	int i;

	i = 0;
	while (str[i] && str[i + 1] != NULL)
	{
		printf("%s ", str[i]);
		i++;		
	}
	if (condition == 0)
		printf("%s", str[i]);
	else
		printf("%s\n", str[i]);
}

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
	if (splited[1] == NULL)
	{
		free(splited[1]);
		value_node = (char *)malloc(sizeof(char));
		value_node[0] = '\0';
		node->value = value_node;
	}
	else
		node->value = splited[1];
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
	
	i = 0;
	envp_list = NULL;
	while (envp[i])
	{
		envp_add_back(&envp_list, creat_node(envp[i]));
		i++;
	}
	return (envp_list);
}

t_envp	*search_key(t_envp *envp_list, char *key)
{
	t_envp	*tmp_envp;

	tmp_envp = envp_list;
	if (!key)
		return (NULL);
	while (tmp_envp)
	{
		if (ft_strcmp(tmp_envp->key, key) == 0)
			return (tmp_envp);
		tmp_envp = tmp_envp->next;
	}
	return (NULL);
}

unsigned int	t_envp_size(t_envp *env_list)
{
	unsigned int	size;
	t_envp			*temp;

	temp = env_list;
	size = 0;
	while (temp)
	{
		size++;
		temp = temp->next;
	}
	return (size);
}

char	**list_to_envp(t_envp *env_list)
{
	char **env_tab;
	t_envp *temp;
	unsigned int i;

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