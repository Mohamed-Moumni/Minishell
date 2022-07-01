/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:26:03 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/06/30 18:44:46 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/builtins.h"
#include "../headers/struct.h"

void	node_init(t_lexer **list, char *word, e_token token)
{
	*list = malloc(sizeof(t_lexer));
	(*list)->next = NULL;
	(*list)->prev = NULL;
	if (token == UNCHECKED)
		specify_operator(word, &token);
	(*list)->token = token;
	(*list)->content = word;
}

void	add_node(t_lexer **list, char *word, e_token token)
{
	t_lexer	*tmp;
	t_lexer	*new_node;

	if (!(*list))
		node_init(list, word, token);
	else
	{	
		tmp = *list;
		node_init(&new_node, word, token);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
		new_node->prev = tmp;
	}
}

int	between_quote(char *line, char *operator, char quote)
{
	char	*first_quote;
	char	*second_quote;

	first_quote = ft_strchr(line, quote);
	if (first_quote[0])
	{
		second_quote = ft_strchr(first_quote + 1, quote);
		if (!second_quote[0])
		{
			printf("error! unmatched quote\n");
			return (-1);
		}
		if (first_quote < operator && second_quote > operator)
			return (0);
	}
	return (1);
}

t_lexer	*get_lexer(char *line)
{
	int			state;
	t_lexer		*list;

	list = NULL;
	state = check_operator(line);
	if (state)
	{
		if (!split_operator(&list, line))
			return NULL;
	}
	else
		add_node(&list, line, WORD);
	if (check_last_node(list) == 0)
	{
		printf("syntax error!\n");
		free_list(list);
		return (NULL);
	}
	return (list);
}

// t_lexer	*get_lexer(char *line)
// {
// 	t_lexer		*list;
// 	char		*start;
// 	char		*word;
// 	int			word_len;

// 	list = NULL;
// 	start = line;
// 	while (start[0] && line[0])
// 	{
// 		start = ft_strchr(line, ' ');
// 		word_len = advanced_strlen(line, start);
// 		if (word_len > 0)
// 		{
// 			word = ft_substr(line, 0, word_len);
// 			start = quote_handle(&word, line, start);
// 			if (!start)
// 				return (NULL);
// 		}
// 		line = start + 1;
// 		add_node(&list, word);
// 	}
// 	return (list);
// }

