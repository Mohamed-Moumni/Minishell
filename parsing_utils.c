/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 08:35:35 by mmoumni           #+#    #+#             */
/*   Updated: 2022/06/13 10:04:44 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	list_size(t_lexer *tokens)
{
	t_lexer	*start;
	t_lexer	*tmp;
	int		size;
	
	if (!tokens)
		return (0);
	start = tokens;
	tmp = tokens->next;
	size = 1;
	while (tmp != start)
	{
		tmp = tmp->next;
		size++;
	}
	return (size);
}

t_ast	*create_node(e_token nodetype, char *value, t_ast *left, t_ast *right)
{
	t_ast *node;

	node = (t_ast *)malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->node_type = nodetype;
	node->value = value;
	node->left = left;
	node->right = right;
	return (node);
}

void	free_tokens(t_lexer **tokens)
{
	t_lexer	*tmp;
	int		size;

	size = list_size(*tokens);
	tmp = *tokens;
	while (tmp->n != size)
	{
		free(tmp);
		tmp = tmp->next;
	}
}
