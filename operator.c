/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-iaz <yait-iaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:50:36 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/06/24 21:11:23 by yait-iaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_node_lex(t_lexer **list, char *line, int *i, int *j)
{
	char	*word;
	int		single_quote;
	int		double_quote;

	single_quote = between_quote(line, &line[*i], '\'');
	double_quote = between_quote(line, &line[*i], '"');
	if (single_quote <= 0 || double_quote <= 0)
	{
		if (single_quote < 0 || double_quote < 0)
			return (-1);
		return (0);
	}
	word = ft_strtrim(ft_strdupi(&line[*j], *i - *j), " ");
	if (!ft_strlen(word))
		return (0);
	add_node(list, word, WORD);
	*j = (*i)++;
	while (line[*i] == '>' || line[*i] == '<')
		(*i)++;
	word = ft_strdupi(&line[*j], *i - *j);
	if (!ft_strlen(word))
		return (0);
	add_node(list, word, UNCHECKED);
	*j = (*i)++;
	return (1);
}

int	check_last_node(t_lexer *list)
{
	t_lexer	*tmp;

	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	if (tmp->token >= 4 && tmp->token <= 8)
		return (0);
	return (1);
}

int	check_operator(char *line)
{
	char	*left;
	char	*pipe;
	char	*right;

	left = ft_strchr(line, '<');
	right = ft_strchr(line, '>');
	pipe = ft_strchr(line, '|');
	if (left[0] || right[0] || pipe[0])
		return (1);
	return (0);
}

int	split_operator(t_lexer **list, char *line)
{
	int	i;
	int	j;
	int	state;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<' || line[i] == '|')
		{
			state = create_node_lex(list, line, &i, &j);
			if (state < 0)
			{
				free_list(*list);
				return (0);
			}
		}
		i++;
	}
	create_node_lex(list, line, &i, &j);
	return (1);
}

void	specify_operator(char *word, e_token *token)
{
	if (!ft_strcmp(word, ">>"))
		*token = DOUBLE_RIGHT_REDIR;
	else if (!ft_strcmp(word, ">"))
		*token = RIGHT_REDIR;
	else if (!ft_strcmp(word, "<<"))
		*token = DOUBLE_LEFT_REDIR;
	else if (!ft_strcmp(word, "<"))
		*token = LEFT_REDIR;
	else if (!ft_strcmp(word, "|"))
		*token = PIPE;
}