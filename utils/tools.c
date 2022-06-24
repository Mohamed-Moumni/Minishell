/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-iaz <yait-iaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:58:42 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/06/16 15:59:05 by yait-iaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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