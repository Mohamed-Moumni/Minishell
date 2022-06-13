/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 08:18:15 by mmoumni           #+#    #+#             */
/*   Updated: 2022/06/13 09:40:44 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*g_tokens;
//<execution> ::= <command>
//            | < execution> '|' <command>

void	next_token(void)
{
	if (list_size(g_tokens) != g_tokens->n)
		g_tokens = g_tokens->next;
}

void	prev_token(void)
{
	if (list_size(g_tokens) != 0)
		g_tokens = g_tokens->prev;
}

t_ast	*execution(void)
{
	t_ast	*tree;
	
	tree = NULL;
	next_token();
	if (g_tokens->content != PIPE)
		tree = command();
	else
		tree = create_node(PIPE, g_tokens->content, execution(), command());
	return (tree);
}

// <command> ::= <simple command>
//             | <simple command> '<' or '<<' <filename>
//             | <simple command> '>' or '>>' <filename>

t_ast	*command(void)
{
	t_ast	*tree;
	t_ast	*filename;
	
	tree = NULL;
	next_token();
	if (g_tokens->content == OPERATOR)
	{
		next_token();
		filename = create_node(FILENAME, g_tokens->content, NULL, NULL);
		prev_token();
		if (g_tokens->content[0] == '>')
		{
			if (g_tokens->content[1] == '>')
				tree = create_node(RRIGHT_OPER, g_tokens->content, simple_command(), filename);
			else
				tree = create_node(RIGHT_OPER, g_tokens->content, simple_command(), filename);
		}
		else
		{
			if (g_tokens->content[0] == '<')
			{
				if (g_tokens->content[1] == '<')
					tree = create_node(LLEFT_OPER, g_tokens->content, simple_command(), filename);
				else
					tree = create_node(LEFT_OPER, g_tokens->content, simple_command(), filename);
			}
		}
	}
	else
	{
		tree = simple_command();
	}
	return (tree);
}

// <simple command> ::= <pahtname>
//             | <simple command> <params>

t_ast	*simple_command(void)
{
	t_ast	*tree;
	t_ast	*pathname;

	tree = NULL;
	next_token();
	if (g_tokens->n == list_size(g_tokens))
	{
		pathname = create_node(PATHNAME, g_tokens->content, NULL, NULL);
		prev_token();
		tree = create_node(CMD, g_tokens->content, pathname, NULL);
	}
	else
	{
		tree->left =
	}
}