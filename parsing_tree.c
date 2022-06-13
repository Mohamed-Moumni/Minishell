/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 08:18:15 by mmoumni           #+#    #+#             */
/*   Updated: 2022/06/13 18:46:27 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer *g_tokens = NULL;

void	next_token(void)
{
	if (g_tokens->n != 4)
		g_tokens = g_tokens->next;
}

void	prev_token(void)
{
	if (list_size(g_tokens) != 0)
		g_tokens = g_tokens->prev;
}

int	expect_token(e_token token)
{
	if (token == g_tokens->token)
		return (1);
	return (0);
}

t_ast	*pipeline(void)
{
	t_ast	*tree;

	tree = NULL;
	tree = command();
	while (g_tokens->token == PIPE)
	{
		next_token();
		tree = create_node(PIPE, "|", tree, command());
		if (g_tokens->n == 4)
			return (tree);
	}
	return (tree);
}

t_ast	*command(void)
{
	t_ast	*tree;

	tree = NULL;
	tree = create_node(CMD, g_tokens->content, NULL, NULL);
	next_token();
	return (tree);	
}

void    display(t_ast *ast)
{
    if (ast == NULL)
        return ;
    display(ast->left);
    display(ast->right);
    printf("%s\n",ast->value);
}

int	main(void)
{
	// t_lexer	*list;

	while (1)
	{
		t_ast *tree;
		g_tokens = get_lexer(readline("@minishell >>"));
		// print_lexer(g_tokens);
		tree = pipeline();
		display(tree);
		
	}
}