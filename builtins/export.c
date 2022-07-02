/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:05:13 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/02 20:21:06 by mmoumni          ###   ########.fr       */
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
	int			opwd_check;

	opwd_check = 0;
	i = 0;
	export = NULL;
	while (env[i])
	{
		splited = ft_split(env[i], '=');
		export_add_back(&export, export_node(ft_append_exp_key(splited[0], &opwd_check), ft_append_dqoute(splited[1], &opwd_check)));
		opwd_check = 0;
		free(splited[0]);
		free(splited[1]);
		free(splited);
		i++;
	}
	return (export);
}

char	*ft_append_dqoute(char *str, int *opwd_check)
{
	char *appended;

	if (*opwd_check == 1)
	{
		appended = (char *)malloc(sizeof(char));
		appended = "";
		return (appended);
	}
	appended = ft_strjoin("\"", str);
	appended = ft_strjoin(appended, "\"");
	return (appended);	
}

char	*ft_append_exp_key(char *str, int *opwd_check)
{
	char *appended;

	if (ft_strcmp(str, "OLDPWD") == 0)
		*opwd_check = 1;		
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

void	ft_export_sort(t_export *list)
{
	t_export	*temp1;
	t_export	*temp2;

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

void	ft_swap(t_export *a, t_export *b)
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
	printf("%s=%s\n",key, value);	
}

void	ft_export(t_export *export, t_char *args)
{
	t_export	*temp;
	t_char		*temp_arg;

	temp = export;
	temp_arg = args;
	if (args->next == NULL)
	{
		while (temp)
		{
			env_with_ex_key(temp->key, temp->value);
			temp = temp->next;
		}
	}
	else
	{
		while(temp_arg)
		{
			export_add_back(&export, export_node(temp_arg->argv, temp_arg->next->next->argv));
			ft_export_sort(export);
			temp_arg = temp_arg->next->next;
		}
	}
}


// t_export	*search_exportkey(t_export *export, char *key)
// {
// 	t_export *tmp_export;

// 	tmp_export = export;
// 	if (!key)
// 		return (NULL);
// 	while (tmp_export)
// 	{
// 		if (ft_strcmp(tmp_export->key, key) == 0)
// 			return (tmp_export);
// 		tmp_export = tmp_export->next;
// 	}
// 	return (NULL);
// }