/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-iaz <yait-iaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:26:03 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/06/12 15:30:15 by yait-iaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	node_init(t_lexer **list, char *word)
{
	static int	n;

	*list = malloc(sizeof(t_lexer));
	(*list)->next = NULL;
	(*list)->prev = NULL;
	(*list)->n = n++;
	(*list)->token = ft_tokenize(&word);
	(*list)->content = word;
}

void	add_node(t_lexer **list, char *word)
{
	t_lexer	*tmp;
	t_lexer	*new_node;

	if (!(*list))
		node_init(list, word);
	else
	{	
		tmp = *list;
		node_init(&new_node, word);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
		new_node->prev = tmp;
	}
}

void	print_lexer(t_lexer *list)
{
	while (list)
	{
		printf("n: %d content: %s ---> token: %d\n", list->n, list->content, \
			list->token);
		list = list->next;
	}
}

t_lexer	*get_lexer(char *line)
{
	t_lexer		*list;
	char		*start;
	char		*word;
	int			word_len;

	list = NULL;
	start = line;
	while (start[0] && line[0])
	{
		start = ft_strchr(line, ' ');
		word_len = advanced_strlen(line, start);
		if (word_len > 0)
		{
			word = ft_substr(line, 0, word_len);
			start = quote_handle(&word, line, start);
			if (!start)
				return (NULL);
		}
		line = start + 1;
		add_node(&list, word);
	}
	return (list);
}
