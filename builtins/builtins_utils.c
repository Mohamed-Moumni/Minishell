/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:53:42 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/20 11:55:26 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/struct.h"
#include "../headers/minishell.h"
#include "../headers/builtins.h"

int	is_nl_valid(char *str)
{
	int	i;

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
	int	i;

	i = 0;
	while (str[i] && str[i + 1] != NULL)
	{
		printf("%s ", str[i]);
		i++;
	}
	if (condition == 0)
	{
		if (!str[i])
			printf("");
		else
			printf("%s", str[i]);
	}
	else
	{
		if (!str[i])
			printf("\n");
		else
			printf("%s\n", str[i]);
	}
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
