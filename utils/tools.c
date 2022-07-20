/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:58:42 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/07/20 09:30:43 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/struct.h"
#include "../headers/minishell.h"
#include "../headers/builtins.h"

void	free_list(t_lexer *list)
{
	t_lexer	*tmp;

	tmp = list;
	while (list)
	{
		list = list->next;
		free(tmp);
		tmp = list;
	}
}

void	free_tab(void **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free (tab[i]);
		i++;
	}
	free(tab);
}

int	ft_isspace(char c)
{
	if (c == '\v' || c == '\n' || c == '\t'
		|| c == '\r' || c == '\f' || c == ' ')
		return (1);
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	advanced_strlen(char *start, char *end)
{
	int	i;

	i = 0;
	while (start[i] && &start[i] != &end[0])
		i++;
	return (i);
}
