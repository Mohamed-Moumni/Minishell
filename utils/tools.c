/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:58:42 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/06/30 13:45:21 by Ma3ert           ###   ########.fr       */
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

void	print_lexer(t_lexer *list)
{
	while (list)
	{
		printf("content: %s ---> token: %d\n", list->content, \
			list->token);
		list = list->next;
	}
}

void	free_tab(char **tab)
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

void	write_in_file(int fd)
{
	char *temp;

	temp = get_next_line(fd);
	while (temp)
	{
		write (fd, temp, ft_strlen(temp));
		free(temp);
		temp = get_next_line(fd);	
	}
	free (temp);
}