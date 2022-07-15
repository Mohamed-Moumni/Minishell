/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 08:47:21 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/15 16:20:27 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../headers/builtins.h"
#include "../headers/minishell.h"
#include "../headers/struct.h"

void	ft_env(t_envp *env, t_char *args)
{
	t_envp	*temp;

	temp = env;
	if (args->next)
	{
		printf("Invalid Syntax\n");
	}
	else
	{
		if (temp->value)
			printf("%s=\"%s\"\n",temp->key,temp->value);
		temp = temp->next;
	}
}

void	env_sort(t_envp *env)
{
	t_envp	*temp1;
	t_envp	*temp2;

	temp1 = env;
	while (temp1)
	{
		temp2 = env;
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