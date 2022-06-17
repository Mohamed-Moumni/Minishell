/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 08:35:35 by mmoumni           #+#    #+#             */
/*   Updated: 2022/06/17 18:02:03 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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

void	free_tree(t_ast	*tree)
{
	if ((tree) == NULL)
		return ;
	free_tree(tree->left);
	free_tree(tree->right);
	free((tree));
}