/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-iaz <yait-iaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:47:30 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/06/10 18:15:53 by yait-iaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// void	check_operation(char *word, e_token *token)
// {
// 	if (ft_strcmp(word, ">") || ft_strcmp(word, ">>") || ft_strcmp(word, "<") \
// 		|| ft_strcmp(word, "<<"))
// 		*token = OPERATOR;
// }

// void	check_term(char *word, e_token *token)
// {
	
// }

// e_token ft_tokenize(char *word)
// {
// 	int		word_len;
// 	e_token	checked;

// 	checked = UNCHECKED;
// 	word_len = ft_strlen(word);
// 	if (word_len == 1 || word_len == 2)
// 		check_operator(word, &checked);
// 	if ((ft_strchr(word, '"') != 0 || ft_strchr(word, '\'')) && checked != UNCHECKED)
// 		check_term(word, &checked);
// 	return ((e_token)checked);
// }

// void	node_init(t_grammar **list, char *word)
// {
// 	static int n;

// 	*list = malloc(sizeof(t_grammar));
// 	(*list)->next = NULL;
// 	(*list)->prev = NULL;
// 	(*list)->n = n++;
// 	(*list)->token = ft_tokenize(word);
// }
// void	add_node(t_grammar **list, char *word)
// {
// 	t_grammar *tmp;
// 	t_grammar *new_node;

// 	if (!list)
// 		node_init(list, word);
// 	tmp = *list;
// 	node_init(new_node, word);
// 	while (tmp->next)
// 		tmp = tmp->next;
// 	tmp->next = new_node;
// 	new_node->prev = tmp;
// }

t_lexer *get_lexer(char *line)
{
	int			i;
	t_lexer		*list;
	char		*start;
	char		*word;
	int			word_len;

	i = 0;
	list = NULL;
	start = line;
	while (line[i])
	{
		start = ft_strchr(line, ' ');
		word_len = advanced_strlen(line, start);
		if (word_len > 0)
		{
			word = ft_substr(line, 0, word_len);
			start = quote_handle(&word, line, start);
			printf("word: %s\n", word);
		}
		line = start + 1;
	}
	return (NULL);
}

int	main(void)
{
	char 		*line;
	t_lexer	*list;

	line = readline("@minishell >>");
	if (line != NULL)
		list = get_lexer(line);
}