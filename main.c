/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:47:30 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/06/17 17:54:55 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	main(void)
// {
// 	t_lexer	*list;

// 	while (1)
// 	{
// 		list = get_lexer(readline("@minishell >> "));
// 		if (list)
// 			print_lexer(list);
// 	}
// }

int	main(void)
{
	t_lexer	*list;

	// while (1)
	// {
	list = get_lexer(readline("@minishell >> "));
	// if (list)
	// 	print_lexer(list);
	t_ast *tree;

	tree = pipeline(list);
	free_tree(tree);
	printf("here\n");
	display(tree);
	// }
}