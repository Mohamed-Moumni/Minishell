/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-iaz <yait-iaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 10:07:54 by mmoumni           #+#    #+#             */
/*   Updated: 2022/06/27 21:25:30 by yait-iaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

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

int	node_char_init(t_char **arg, char *word)
{
	*arg = malloc(sizeof(t_char));
	if (!(*arg))
		return (0);
	(*arg)->argv = word;
	(*arg)->next = NULL;
	return (1);
}

int	add_char_node(t_char **arg, char *word)
{
	t_char	*tmp;
	t_char	*new_node;

	if (!(*arg))
	{
		if (!node_char_init(arg, word))
			return (0);
	}
	else
	{	
		tmp = *arg;
		if (!node_char_init(&new_node, word))
			return (0);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
	return (1);
}

void	print_char(t_char *ch)
{
	t_char *tmp;

	tmp = ch;
	while (tmp)
	{
		printf("arg: %s\n", tmp->argv);
		tmp = tmp->next;
	}
}

int	element_count(t_char *list)
{
	int	n;
	t_char	*tmp;

	n = 0;
	tmp = list;
	while (tmp)
	{
		n++;
		tmp = tmp->next;
	}
	return (n);
}

int	treat_word(t_cmds *cmds, t_lexer *node, e_token token)
{
	char		*start;
	char		*word;
	int			word_len;

	if (!add_node_cmd(&cmds, WORD))
		return (0);
	start = node->content;
	while (start[0] && node->content[0])
	{
		start = ft_strchr(node->content, ' ');
		word_len = advanced_strlen(node->content, start);
		if (word_len > 0)
		{
			word = ft_substr(node->content, 0, word_len);
			start = quote_handle(&word, node->content, start);
			if (!start)
				return (0);
		}
		node->content = start + 1;
		if (!add_char_node(&cmds->argv, word))
			return (0);
	}
	print_char(cmds->argv);
	return (1);
}

int	treat_redir(t_cmds *cmds, t_lexer *node, e_token token)
{
	
}

int start_execution(t_lexer *list)
{
	t_cmds	*cmds;
	t_lexer	*tmp;

	tmp = list;
	cmds = NULL;
	while (tmp)
	{
		if (tmp->token == 0)
		{
			if (!treat_word(cmds, tmp, WORD))
				return (0);
		}
		else
		{
			if (!treat_redir(cmds, tmp, UNCHECKED))
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

// void	run_pipe(t_cmds *cmds)
// {
	
// }

// void	run_redirection(t_cmds *cmds)
// {
	
// }

