/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 08:18:15 by mmoumni           #+#    #+#             */
/*   Updated: 2022/06/14 12:04:21 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*next_token(t_lexer *tokens)
{
	if (tokens)
		tokens = tokens->next;
	return (tokens);
}

// t_ast	*pipeline(t_lexer *tokens)
// {
// 	t_ast	*tree;

// 	tree = NULL;
// 	tree = command(tokens);
// 	while (next_pipe(tokens) != NULL)
// 	{
// 		tree = create_node(PIPE, "|", tree, command());
// 		if (tokens == NULL)
// 			return (tree);
// 	}
// 	return (tree);
// }

// t_ast	*command(t_lexer *tokens)
// {
// 	t_ast	*tree;

// 	tree = NULL;
// 	tree = simple_command(tokens);
// 	while (next_operator(tokens, '<') || next_operator(tokens, '<<'))
// 	{
// 		tree = create_node(OPERATOR, "< | <<", tree, filename);
// 		if (tokens == NULL)
// 			return (tree);
// 	}
// 	while (next_operator(tokens, '>') || next_operator(tokens, '>>'))
// 	{
// 		tree = create_node(OPERATOR, "> | >>", tree, filename);
// 		if (tokens == NULL)
// 			return (tree);
// 	}
// 	return (tree);	
// }

// // <simple command> ::= <pahtname>
//             | <simple command> <params>

t_ast	*simple_command(t_lexer **tokens)
{
	t_ast	*tree;

	tree = NULL;
	printf("%d\n",is_pathname(*tokens));
	if (is_pathname(*tokens) == 1)
	{
		tree = create_node(PATHNAME, (*tokens)->content, NULL, NULL);
		*tokens = next_token(*tokens);
		if ((*tokens) == NULL)
			return (tree);
	}
	else
	{
		*tokens = next_token(*tokens);
		tree = simple_command(tokens);
		tree->left = create_node(PARAMS, (*tokens)->content, NULL, NULL);
	}
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
	t_lexer	*tokens;

	while (1)
	{
		t_ast *tree;
		tokens = get_lexer(readline("@minishell >>"));
		// while (tokens != NULL)
		// {
		// 	printf("%s\n",tokens->content);
		// 	g_tokens = g_tokens->next;
		// }
		// print_lexer(g_tokens);
		// tree = pipeline();
		tree = simple_command(&tokens);
		// display(tree);
		
	}
}