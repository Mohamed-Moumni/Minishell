/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 08:18:15 by mmoumni           #+#    #+#             */
/*   Updated: 2022/06/14 18:00:48 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*next_token(t_lexer *tokens)
{
	if (tokens)
		tokens = tokens->next;
	return (tokens);
}

t_ast	*pipeline(t_lexer *tokens)
{
	t_ast	*tree;

	tree = NULL;
	tree = command(tokens);
	printf("%s\n",tokens->content);
	while (tokens->token == PIPE)
	{
		tree = create_node(PIPE, "|", tree, command(tokens));
		if (tokens == NULL)
			return (tree);
	}
	return (tree);
}

t_ast	*command(t_lexer *tokens)
{
	t_ast	*tree;

	tree = NULL;
	if (tokens == NULL)
		return (NULL);
	tree = simple_command(tokens);
	while (tokens->token != PIPE && tokens->token != OPERATOR)
		tokens = tokens->next;
	while (ft_strcmp(tokens->content, "<") == 0 || ft_strcmp(tokens->content, "<<") == 0 ||
		ft_strcmp(tokens->content, ">") == 0 || ft_strcmp(tokens->content, ">>") == 0)
	{
		if (ft_strcmp(tokens->content, "<") == 0)
		{
			tokens = tokens->next;
			tree = create_node(OPERATOR, "<", tree, create_node(FILENAME, tokens->content, NULL, NULL));
			tokens = tokens->next;
		}
		else if (ft_strcmp(tokens->content, "<<") == 0)
		{
			tokens = tokens->next;
			tree = create_node(OPERATOR, "<<", tree, create_node(FILENAME, tokens->content, NULL, NULL));
			tokens = tokens->next;
		}
		else if (ft_strcmp(tokens->content, ">") == 0)
		{
			tokens = tokens->next;
			tree = create_node(OPERATOR, ">", tree, create_node(FILENAME, tokens->content, NULL, NULL));
			tokens = tokens->next;
		}
		else if (ft_strcmp(tokens->content, ">>") == 0)
		{
			tokens = tokens->next;
			tree = create_node(OPERATOR, ">>", tree, create_node(FILENAME, tokens->content, NULL, NULL));
			tokens = tokens->next;
		}
		if (tokens == NULL)
			return (tree);
	}
	return (tree);	
}

// // <simple command> ::= <pahtname>
//             | <simple command> <params>

t_ast	*simple_command(t_lexer *tokens)
{
	t_ast	*tree;
	t_lexer	tok;

	tree = NULL;
	if (tokens == NULL)
		return (tree);
	if (is_pathname(tokens) == 1)
		tree = create_node(PATHNAME, (tokens)->content, NULL, NULL);
	else
	{
		tok = *tokens;
		tokens = next_token(tokens);
		tree = simple_command(tokens);
		tree = create_node(PARAMS, (tok).content, tree, NULL);
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
	t_lexer	*tokens = NULL;

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
		tree = pipeline(tokens);
		display(tree);
	}
}