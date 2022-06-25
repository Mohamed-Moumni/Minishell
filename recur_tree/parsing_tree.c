/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 08:18:15 by mmoumni           #+#    #+#             */
/*   Updated: 2022/06/17 18:02:37 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*next_token(t_lexer *tokens)
{
	if (tokens)
		tokens = tokens->next;
	return (tokens);
}

t_ast	*pipeline(t_lexer *lex)
{
	t_ast	*tree;

	tree = NULL;
	tree = command(&lex);
	if (lex == NULL)
		return (NULL);
	while (lex && lex->token == PIPE)
	{
		lex = next_token(lex);
		tree = create_node(PIPE, "|", tree, command(&lex));
		if (lex == NULL)
			return (tree);
	}
	return (tree);
}


t_ast	*command(t_lexer **lex)
{
	t_ast	*tree;

	tree = NULL;
	if ((*lex) && (*lex)->token == WORD)
	{
		tree = create_node(WORD, (*lex)->content, NULL, NULL);
		(*lex) = next_token((*lex));
	}
	while ((*lex) && ((*lex)->token == LEFT_REDIR
		|| (*lex)->token == DOUBLE_LEFT_REDIR
		|| (*lex)->token == RIGHT_REDIR
		|| (*lex)->token == DOUBLE_RIGHT_REDIR))
	{
		redirection(&tree, lex);
		(*lex) = next_token((*lex));
		if ((*lex) == NULL)
			return (tree);	
	}	
	return (tree);
}

void	redirection(t_ast **tree, t_lexer **lex)
{
	if ((*lex)->token == LEFT_REDIR)
	{
		(*lex) = next_token((*lex));
		(*tree) = create_node(LEFT_REDIR, "<", (*tree), create_node(FILENAME, (*lex)->content, NULL, NULL));
	}
	else if ((*lex)->token == DOUBLE_LEFT_REDIR)
	{
		(*lex) = next_token((*lex));
		(*tree) = create_node(DOUBLE_LEFT_REDIR, "<<", (*tree), create_node(FILENAME, (*lex)->content, NULL, NULL));
	}
	else if ((*lex)->token == RIGHT_REDIR)
	{
		(*lex) = next_token((*lex));
		(*tree) = create_node(RIGHT_REDIR, ">", (*tree), create_node(FILENAME, (*lex)->content, NULL, NULL));
	}
	else if ((*lex)->token == DOUBLE_RIGHT_REDIR)
	{
		(*lex) = next_token((*lex));
		(*tree) = create_node(DOUBLE_RIGHT_REDIR, ">>", (*tree), create_node(FILENAME, (*lex)->content, NULL, NULL));
	}
}

void    display(t_ast *ast)
{
    if (ast == NULL)
        return ;
    display(ast->left);
    display(ast->right);
    printf("%s\n",ast->value);
}
