/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:32:58 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/20 09:36:28 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/struct.h"
#include "../headers/minishell.h"
#include "../headers/builtins.h"

void	free_tchar(t_char **tchar)
{
	t_char	*temp;
	t_char	*next;

	temp = *tchar;
	while (temp)
	{
		next = temp->next;
		free(temp);
		temp = next;
	}
}

void	free_cmd_list(t_cmds **cmds)
{
	t_cmds	*temp;

	temp = *cmds;
	while (temp)
	{
		free_tchar(&temp->argv);
		temp = temp->next;
	}
}

void	free_lexer(t_lexer **lexer)
{
	t_lexer	*temp;
	t_lexer	*next;

	temp = *lexer;
	while (temp)
	{
		next = temp->next;
		free(temp->content);
		temp = next;
	}	
}

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
