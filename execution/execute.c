/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 10:07:54 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/19 21:53:16 by Ma3ert           ###   ########.fr       */
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
		printf("arg: \n%s\n", tmp->argv);
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

t_cmds	*cmd_last_node(t_cmds *cmd)
{
	t_cmds	*tmp;

	tmp = cmd;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

int	treat_word(t_cmds **cmds, t_lexer *node, t_envp **env, e_token token)
{
	char	*start;
	char	*end;
	char	*word;

	if (!add_node_cmd(cmds, token))
		return (0);
	if (node->prev && node->prev->token == HEREDOC && node->token != SINGLE_QUOTE)
	{
		ft_expand(&(node->content), env, node);
		return (add_char_node(&cmd_last_node(*cmds)->argv, ft_strdupi(node->content, ft_strlen(node->content))));
	}
	node->content = ft_strtrim(node->content, " ");
	start = node->content;
	end = start;
	while (start[0] && end[0])
	{
		end++;
		if ((end[0] == ' ' && between_quote(start, end, '"') \
			&& between_quote(start, end, '\'')) || !end[0])
		{
			if (start[0] != ' ')
			{	
				word = hundle_quote(ft_substr(start, 0, \
					advanced_strlen(start, end)), env, node);
				if (!word)
					return (0);
				if (!add_char_node(&cmd_last_node(*cmds)->argv, word))
					return (0);
			}
			start = end + 1;
		}
	}
	return (1);
}

t_char	*char_last_node(t_char *node)
{
	t_char *ch;

	ch = node;
	while (ch->next)
		ch = ch->next;
	return (ch);
}

void	add_front_node_cmd(t_cmds **cmd, t_char *tmp, e_token token)
{
	t_cmds *new_node;
	t_cmds *old_head;

	old_head = *cmd;
	new_node = NULL;
	add_node_cmd(&new_node, token);
	new_node->argv = tmp;
	old_head->prev = new_node;
	new_node->next = old_head;
	*cmd = new_node;
}

int	adjust_filename(t_cmds **cmd)
{
	t_char	*tmp;
	t_cmds	*node;
	t_cmds	*prev_cmd;

	node = cmd_last_node(*cmd);
	tmp = node->argv->next;
	node->argv->next = NULL;
	prev_cmd = node->prev;
	while (prev_cmd && prev_cmd->type != WORD)
		prev_cmd = prev_cmd->prev;
	if (!prev_cmd)
		add_front_node_cmd(cmd, tmp, WORD);
	else
		char_last_node(prev_cmd->argv)->next = tmp;
	return (1);
}

int	treat_redir(t_cmds **cmds, t_envp **env, t_lexer *node)
{
	t_cmds	*tmp;

	if (!treat_word(cmds, node->next, env, node->token))
		return (0);
	tmp = *cmds;
	while (tmp->next)
		tmp = tmp->next;
	if (element_count(tmp->argv) > 1 && node->token != PIPE)
		adjust_filename(cmds);
	return (1);
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

int start_execution(t_lexer *list, t_envp **env)
{
	t_cmds	*cmds;
	t_lexer	*tmp;

	tmp = list;
	cmds = NULL;
	while (tmp)
	{
		if (tmp->token == WORD)
		{
			if (!treat_word(&cmds, tmp, env, WORD))
				return (0);
		}
		else
		{
			if (!treat_redir(&cmds, env, tmp))
				return (0);
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	// print_cmd(cmds);
	begin_execution(cmds, env);
	return (1);
}

int	**two_dim_arr(int a)
{
	int i;
	int	**tab;

	tab = (int **)malloc(sizeof(int *) * (a + 1));
	i = 0;
	while (i < a)
	{
		tab[i] = (int *)malloc(sizeof(int) * 2);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

