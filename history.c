/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 21:01:58 by mmoumni           #+#    #+#             */
/*   Updated: 2022/06/16 21:14:47 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hist	*add_to_history(t_hist *old_hist, t_hist *new_hist)
{
	t_hist	*temp_hist;

	temp_hist = old_hist;
	if (old_hist == NULL)
		old_hist = new_hist;
	while (temp_hist->next)
	{
		temp_hist = temp_hist->next;	
	}
	temp_hist->next = new_hist;
	return (old_hist);
}

t_hist	*create_hist(char *str)
{
	t_hist	*node;

	node = (t_hist *)malloc(sizeof(t_hist));
	if (!node)
		return (NULL);
	node->histo = str;
	node->next = NULL;
	return (node);
}

int main(void)
{
	t_hist	*history;
	char	*read_line;

	history = NULL;
	while ((read_line = readline("enter a command")))
	{
		history = add_to_history(history, create_hist(read_line));
	}
	t_hist	*tmp;

	tmp = history;
	while (tmp)
	{
		printf("%s\n",tmp->histo);
		tmp = tmp->next;
	}
	return (0);
}