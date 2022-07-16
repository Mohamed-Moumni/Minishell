/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 17:19:26 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/16 17:26:53 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/builtins.h"
#include "../headers/minishell.h"
#include "../headers/struct.h"

void	ft_unset(t_envp **env, t_char *args)
{
    t_char  *temp;

    temp = args;
    while (temp)
    {
        if (!valid_unset(args->argv))
            printf("minishell: unset: `%s': not a valid identifier\n",args->argv);
		else
		{
			if (!ft_strcmp(args->argv, "PATH"))
				g_minishell.unset_path = 1;
			delete_node(env, temp);
			// printf("%s\n", (env)->key);
		}
		temp = temp->next;
    }
}

t_envp	*delete_head(t_envp *head)
{
	t_envp *temp;
	t_envp	*next;
	
	temp = head;
	next = head->next;
	free(temp);
	return (next); 
}

void	delete_node(t_envp **env, t_char *arg)
{
	t_envp	*next;
	t_envp	*temp;

	if (!ft_strcmp(arg->argv, (*env)->key))
	{
		temp = *env;
		*env = temp->next;
		free(temp);
	}
	else
	{
		temp = *env;
		while (temp)
		{
			if (temp->next && !ft_strcmp(temp->next->key, arg->argv))
			{
				next = temp->next;
				temp->next = next->next;
				free(next);
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
