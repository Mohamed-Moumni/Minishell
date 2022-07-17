/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:05:13 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/17 16:59:22 by mmoumni          ###   ########.fr       */
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
		add_export_vars(env, args->next);
	}
	else
	{
		tem_env = *env;
		env_sort(*env);
		while (tem_env)
		{
			if (!ft_strcmp(tem_env->value, ""))
				printf("%s%s\n",EXPORT_KEY, tem_env->key);
			else
				if (ft_strcmp(tem_env->key, "_"))
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

void	ft_split_key_val(char *str, char c, char **key, char **value)
{
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	while (str[i] != c)
		i++;
	*key = ft_strdupi(str, i);
	*value = ft_strdup((str + i + 1));
}
void	trait_arg(t_envp **env, t_char *arg)
{
	t_envp	*node;
	t_envp	*s_key;
	
	if (!valid_arg(arg->argv))
	{
		printf("minishell: export: `%s': not a valid identifier\n", arg->argv);
		g_minishell.exit_status = 1;
	}
	else if (ft_strchr(arg->argv, '=')[0])
	{
		node = (t_envp *)malloc(sizeof(t_envp));
		ft_split_key_val(arg->argv, '=', &node->key, &node->value);
		node->next = NULL;
		s_key = search_key(*env, node->key);
		if (s_key && !ft_strcmp(s_key->key, node->key))
		{
			free(s_key->value);
			s_key->value = node->value;
			free(node->key);
			free(node);
		}
		else
			envp_add_back(env, node);
	}
	else
	{
		node = (t_envp *)malloc(sizeof(t_envp));
		node->key = ft_strdup(arg->argv);
		node->value = ft_strdup("");
		node->next = NULL;
		envp_add_back(env, node);
	}
}

int	valid_arg(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i] && (ft_isalpha(str[i]) || ft_isdigit(str[i])
		|| str[i] == '_' || str[i] == '='))
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	if (str[i] != '\0')
		return (0);
	return (1);
}
