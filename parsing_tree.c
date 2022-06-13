/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 08:18:15 by mmoumni           #+#    #+#             */
/*   Updated: 2022/06/13 08:55:42 by mmoumni          ###   ########.fr       */
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
	{
		tree = command();
	}
	else
	{
		tree = create_node(PIPE, "|", execution(), command())
	}
	return (tree);
}

// <command> ::= <simple command>
//             | <simple command> '<' or '<<' <filename>
//             | <simple command> '>' or '>>' <filename>

t_ast	*command(void)
{
	t_ast	*tree;
	
	tree = NULL;
	next_token();
	if (g_tokens->content == OPERATOR)
	{
		
	}
	else
	{
		tree = simple_command();
	}
	return (tree);
}