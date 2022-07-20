/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 19:02:52 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/07/20 20:55:25 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/struct.h"
#include "../headers/minishell.h"
#include "../headers/builtins.h"

int	node_init_cmd(t_cmds **list, e_token token)
{
	*list = malloc(sizeof(t_cmds));
	if (!(*list))
		return (0);
	(*list)->next = NULL;
	(*list)->prev = NULL;
	(*list)->argv = NULL;
	(*list)->type = token;
	return (1);
}

int	add_node_cmd(t_cmds **cmds, e_token token)
{
	t_cmds	*tmp;
	t_cmds	*new_node;

	if (!(*cmds))
	{
		if (!node_init_cmd(cmds, token))
			return (0);
	}
	else
	{	
		tmp = *cmds;
		if (!node_init_cmd(&new_node, token))
			return (0);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
		new_node->prev = tmp;
	}
	return (1);
}

void	add_front_node_cmd(t_cmds **cmd, t_char *tmp, e_token token)
{
	t_cmds	*new_node;
	t_cmds	*old_head;

	old_head = *cmd;
	new_node = NULL;
	add_node_cmd(&new_node, token);
	new_node->argv = tmp;
	old_head->prev = new_node;
	new_node->next = old_head;
	*cmd = new_node;
}

t_cmds	*cmd_last_node(t_cmds *cmd)
{
	t_cmds	*tmp;

	tmp = cmd;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
