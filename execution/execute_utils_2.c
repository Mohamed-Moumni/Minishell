/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:34:05 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/01 17:19:30 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/builtins.h"
#include "../headers/struct.h"
#include "../headers/minishell.h"

unsigned int	t_char_size(t_char *tchar_list)
{
	unsigned int	size;
	t_char			*temp;

	temp = tchar_list;
	size = 0;
	while (temp)
	{
		size++;
		temp = temp->next;
	}
	return (size);
}

char **conv_t_char_to_tab(t_char *tchar_list)
{
	t_char	*temp;
	char	**tab;
	unsigned int i;

	i = 0;
	temp = tchar_list;
	tab = (char **)malloc(sizeof(char *) * (t_char_size(tchar_list) + 1));
	if (!tab)
		return (NULL);
	while (temp)
	{
		tab[i] = temp->argv;
		i++;
		temp = temp->next;
	}
	tab[i] = NULL;
	return (tab);
}

unsigned int	how_many_pipes(t_cmds *cmds)
{
	t_cmds			*temp;
	unsigned int	i;

	i = 0;
	temp = cmds;
	while (temp)
	{
		if (temp->type == PIPE)
			i++;
		temp = temp->next;
	}
	return (i);
}

void	index_cmds(t_cmds **cmds)
{
	t_cmds			*temp;
	unsigned int	i;

	i = 0;
	temp = *cmds;
	while (temp)
	{
		temp->index = i;
		temp = temp->next;
	}
}