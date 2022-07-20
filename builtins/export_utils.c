/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 12:52:51 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/20 12:54:16 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/struct.h"
#include "../headers/minishell.h"
#include "../headers/builtins.h"

void	trait_arg(t_envp **env, t_char *arg)
{
	t_envp	*node;

	if (!valid_arg(arg->argv))
	{
		printf("minishell: export: `%s': not a valid identifier\n", arg->argv);
		g_minishell.exit_status = 1;
	}
	else if (ft_strchr(arg->argv, '=')[0])
		add_arg_trait(env, arg);
	else
	{
		node = (t_envp *)malloc(sizeof(t_envp));
		node->key = ft_strdup(arg->argv);
		node->value = ft_strdup("");
		node->next = NULL;
		envp_add_back(env, node);
	}
}

void	add_arg_trait(t_envp **env, t_char *arg)
{
	t_envp	*node;
	t_envp	*s_key;

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
