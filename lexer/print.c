/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 21:27:59 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/07/21 15:57:09 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/struct.h"
#include "../headers/minishell.h"
#include "../headers/builtins.h"

void	print_char(t_char *ch)
{
	t_char	*tmp;

	tmp = ch;
	while (tmp)
	{
		printf("arg: \n%s\n", tmp->argv);
		tmp = tmp->next;
	}
}

void	print_cmd(t_cmds *cmd)
{
	while (cmd)
	{
		printf("----------------------------\n");
		print_char(cmd->argv);
		printf("token: %d\n", cmd->type);
		printf("-----------------------\n");
		cmd = cmd->next;
	}
}

void	print_lexer(t_lexer *list)
{
	while (list)
	{
		printf("content: |%s| ---> token: %d\n", list->content, \
			list->token);
		list = list->next;
	}
}

void	set_token(t_lexer *node)
{
	char	*double_quote;
	char	*single_quote;

	double_quote = ft_strchr(node->content, '"');
	single_quote = ft_strchr(node->content, '\'');
	if (double_quote[0] || single_quote[0])
		node->token = SINGLE_QUOTE;
}
