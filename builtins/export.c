/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:05:13 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/01 12:02:19 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/struct.h"
#include "../headers/minishell.h"
#include "../headers/builtins.h"

t_export	*export_node(char *key, char *value)
{
	t_export	*node;

	node = (t_export *)malloc(sizeof(t_export));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

t_export	*env_to_expo_list(char **env)
{
	t_export	*export;
	int			i;
	char		**splited;
	i = 0;
	export = NULL;
	while (env[i])
	{
		splited = ft_split(env[i], '=');
		export_add_back(&export, export_node(ft_append_exp_key(splited[0]), ft_append_dqoute(splited[1])));
		free(splited[0]);
		free(splited[1]);
		free(splited);
		i++;
	}
	return (export);
}

char	*ft_append_dqoute(char *str)
{
	char *appended;

	appended = ft_strjoin("\"", str);
	appended = ft_strjoin(appended, "\"");
	return (appended);	
}

char	*ft_append_exp_key(char *str)
{
	char *appended;

	appended = ft_strjoin(EXPORT_KEY, str);
	return (appended);
}

void	export_add_back(t_export **export, t_export *new)
{
	t_export *temp;

	if (*export == NULL)
		(*export) = new;
	else
	{
		temp = last_expo(*export);
		temp->next = new;
	}
}

t_export	*last_expo(t_export *export)
{
	t_export *temp;

	temp = export;
	while (temp->next)
	{
		temp = temp->next;
	}
	return (temp);
}

void	ft_env_sort(t_envp *list)
{
	t_envp	*temp1;
	t_envp	*temp2;

	temp1 = list;
	while (temp1)
	{
		temp2 = list;
		while (temp2)
		{
			if (ft_strcmp(temp1->key, temp2->key) <= 0)
				ft_swap(temp1, temp2);
			temp2 = temp2->next;	
		}
		temp1 = temp1->next;
	}
}

void	ft_swap(t_envp *a, t_envp *b)
{
	char	*temp_key;
	char	*temp_value;

	temp_key = a->key;
	temp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = temp_key;
	b->value = temp_value;
}

void	env_with_ex_key(char *key, char *value)
{
	printf("%s ",EXPORT_KEY);
	printf("%s=\"%s\"\n",key, value);	
}

void	ft_export(t_envp *envp_list)
{
	t_envp	*temp;

	temp = envp_list;
	ft_env_sort(envp_list);
	while (temp)
	{
		env_with_ex_key(temp->key, temp->value);
		temp = temp->next;
	}
}

// int	main(int ac, char **av, char **env)
// {
// 	t_envp	*temp;

// 	temp = envp_to_list(env);
// 	ft_env_sort(temp);
// 	ft_export(temp);
// 	return (0);
// }