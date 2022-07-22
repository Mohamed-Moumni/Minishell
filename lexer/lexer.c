/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:26:03 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/07/21 14:42:27 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/builtins.h"
#include "../headers/struct.h"

int	node_init(t_lexer **list, char *word, t_token token)
{
	int	state;

	state = 1;
	*list = malloc(sizeof(t_lexer));
	(*list)->next = NULL;
	(*list)->prev = NULL;
	if (token == UNCHECKED)
		state = specify_operator(word, &token);
	if (!state)
		return (0);
	(*list)->token = token;
	(*list)->content = word;
	return (state);
}

int	add_node(t_lexer **list, char *word, t_token token)
{
	int		state;
	t_lexer	*tmp;
	t_lexer	*new_node;

	if (!(*list))
		state = node_init(list, word, token);
	else
	{	
		tmp = *list;
		state = node_init(&new_node, word, token);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
		new_node->prev = tmp;
	}
	return (state);
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
			return (1);
		if (first_quote < operator && second_quote > operator)
			return (0);
	}
	return (1);
}

void	add_front_lexer(t_lexer **head, char *word, t_token token)
{
	t_lexer	*new_node;
	t_lexer	*old_head;

	old_head = *head;
	new_node = NULL;
	add_node(&new_node, word, token);
	new_node->content = word;
	old_head->prev = new_node;
	new_node->next = old_head;
	*head = new_node;
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
			return (NULL);
	}
	else
		add_node(&list, ft_strdup(line), WORD);
	if (check_last_node(list) == 0)
	{
		printf("syntax error!\n");
		free_list(list);
		return (NULL);
	}
	return (list);
}
