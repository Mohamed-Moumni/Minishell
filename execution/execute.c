/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 10:07:54 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/21 14:25:49 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/struct.h"
#include "../headers/minishell.h"
#include "../headers/builtins.h"

int	adjust_arg(char *start, t_lexer *node, t_envp **env, t_cmds *cmd)
{
	char	*end;
	char	*word;

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
				if (!add_char_node(&cmd_last_node(cmd)->argv, word))
					return (0);
			}
			start = end + 1;
		}
	}
	return (1);
}

int	treat_word(t_cmds **cmds, t_lexer *node, t_envp **env, t_token token)
{
	char	*start;

	if (!add_node_cmd(cmds, token))
		return (0);
	if (node->prev && node->prev->token != HEREDOC)
	{
		printf("I get in\n");
		ft_expand(&(node->content), env, node);
		return (add_char_node(&cmd_last_node(*cmds)->argv, \
			ft_strdupi(node->content, ft_strlen(node->content))));
	}
	node->content = ft_strtrim(node->content, " ");
	start = node->content;
	if (!adjust_arg(start, node, env, *cmds))
		return (0);
	return (1);
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

int	start_execution(t_lexer *list, t_envp **env)
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
	begin_execution(cmds, env);
	free_cmd_list(&cmds);
	return (1);
}
