/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 17:19:26 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/15 16:18:56 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/builtins.h"
#include "../headers/minishell.h"
#include "../headers/struct.h"

void	ft_unset(t_envp *env, t_char *args)
{
    t_char  *temp;

    temp = args;
    while (temp)
    {
        if (!valid_unset(args->argv))
            printf("minishell: unset: `args->argv': not a valid identifier");
		else
		{
			delete_node(&env, args);
		}
		temp = temp->next;
    }
}

void    delete_node(t_envp **env, t_char *arg)
{
	t_envp	*prev;
	t_envp	*next;
	t_envp	*temp;
	
	if (!ft_strcmp(arg->argv, (*env)->key))
	{
		temp = *env;
		*env = (*env)->next;
		free(temp);
	}
	else
	{
		temp = *env;
		while (temp)
		{
			if (temp->next && !ft_strcmp(temp->next->key, arg->argv))
			{
				prev = temp;
				next = temp->next->next;
				free (temp);
				prev->next = next;
			}
			temp = temp->next;
		}
	}
}

int valid_unset(char *str)
{
    int i;

    i = 0;
	while (str[i] && (ft_isalpha(str[i]) || str[i] == '_' || ft_isdigit(str[i])))
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}