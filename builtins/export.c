/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:05:13 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/16 17:26:34 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/struct.h"
#include "../headers/minishell.h"
#include "../headers/builtins.h"

void	ft_export(t_envp **env, t_char *args)
{
	t_char	*temp;
	t_envp	*tem_env;
	
	temp = args;
	if (args->next)
	{
		// add_export_vars(&env, args->next);
	}
	else
	{
		tem_env = *env;
		while (tem_env)
		{
			if (!ft_strcmp(tem_env->value, ""))
				printf("%s%s\n",EXPORT_KEY, tem_env->key);
			else
				if (ft_strcmp(tem_env->key, USRBINENV))
					printf("%s%s=\"%s\"\n",EXPORT_KEY ,tem_env->key ,tem_env->value);
			tem_env = tem_env->next;
		}	
	}
}

void	add_export_vars(t_envp **env, t_char *args)
{
	t_char	*temp;

	temp = args;
	while (temp)
	{
		trait_arg(env, temp);
		temp = temp->next;
	}
}

void	trait_arg(t_envp **env, t_char *arg)
{
	t_envp	*node;

	if (!valid_arg(arg->argv))
	{
		printf("minishell: export: `%s': not a valid identifier\n", arg->argv);
		exit (EXIT_FAILURE);
	}
	if (ft_strchr(arg->argv, '+'))
	{
		node = (t_envp *)malloc(sizeof(t_envp));
		get_key_value(arg->argv, &node->key, &node->value, 0);
		node->next = NULL;
		(*env)->next = node;
	}
	else if (ft_strchr(arg->argv, '='))
	{
		node = (t_envp *)malloc(sizeof(t_envp));
		get_key_value(arg->argv, &node->key, &node->value, 1);
		node->next = NULL;
		(*env)->next = node;
	}
	else
	{
		node = (t_envp *)malloc(sizeof(t_envp));
		get_key_value(arg->argv, &node->key, &node->value, 2);
		node->next = NULL;
		(*env)->next = node;
	}
}

void	get_key_value(char *str, char **key, char **value, int cond)
{
	int	i;
	int	size;

	i = 0;
	if (cond == 0)
	{
		size = (int)(str - ft_strchr(str, '+'));
		*key = (char *)malloc(sizeof(char) * (size + 1));
		while (str[i] != '+')
		{
			*key[i] = str[i];
			i++;
		}
		i = i + 2;
		*value = (char *)malloc(sizeof(char) * (ft_strlen(str) - size + 2) + 1);
		while (str[i])
		{
			*value[i] = str[i];
			i++;
		}
	}
	else if (cond == 1)
	{
		size = (int)(str - ft_strchr(str, '='));
		*key = (char *)malloc(sizeof(char) * (size + 1));
		while (str[i] != '=')
		{
			*key[i] = str[i];
			i++;
		}
		i = i + 1;
		*value = (char *)malloc(sizeof(char) * (ft_strlen(str) - size + 1) + 1);
		while (str[i])
		{
			*value[i] = str[i];
			i++;
		}
	}
	else
	{
		*key = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
		while (str[i])
		{
			*key[i] = str[i];
			i++;
		}
		*value = (char *)malloc(sizeof(char));
		*value[0] = '\0';
	}
}

int	valid_arg(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i] && (ft_isalpha(str[i]) || ft_isdigit(str[i])
		|| str[i] == '_' || str[i] == '=' || str[i] == '+'))
	{
		if (str[i] == '+')
		{
			if (str[i + 1] && str[i + 1] == '=')
				return (1);
		}
		else if (str[i] == '=')
			return (1);
		i++;
	}
	if (str[i] != '\0')
		return (0);
	return (1);
}
