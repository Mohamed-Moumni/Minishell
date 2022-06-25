/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-iaz <yait-iaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:47:30 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/06/25 15:02:00 by yait-iaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_content(t_lexer *node)
{
	char	*line;
	char	*new_content;

	if (!node)
		return ;
	line = readline("> ");
	new_content = ft_strdupi("", 0);
	while (ft_strcmp(line, node->content))
	{
		printf("line: %s\n", line);
		line = ft_strjoin(line, "\n");
		new_content = ft_strjoin(new_content, line);
		printf("new content:\n%s", new_content);
		line = readline("> ");
	}
	free(node->content);
	node->content = new_content;
}

void	adjust_heredoc(t_lexer *list)
{
	t_lexer	*node;

	node = list;
	while (node)
	{
		if (!ft_strcmp(node->content, "<<"))
			replace_content(node->next);
		node = node->next;
	}
}

int	main(void)
{
	t_lexer	*list;

	while (1)
	{
		list = get_lexer(readline("@minishell >> "));
		adjust_heredoc(list);
		if (list)
			print_lexer(list);
	}
}
