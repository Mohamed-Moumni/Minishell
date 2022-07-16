/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:50:36 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/07/16 18:55:13 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/struct.h"
#include "../headers/minishell.h"
#include "../headers/builtins.h"

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
	if (!add_node(list, word, WORD))
		return (-1);
	*j = (*i)++;
	while (line[*i] == '>' || line[*i] == '<' || line[*i] == '|')
		(*i)++;
	word = ft_strdupi(&line[*j], *i - *j);
	if (!ft_strlen(word))
		return (0);
	if (!add_node(list, word, UNCHECKED))
		return (-1);
	*j = (*i)++;
	return (1);
}

int	check_last_node(t_lexer *list)
{
	t_lexer	*tmp;

	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	printf("content: %s\n", tmp->content);
	if ((tmp->token >= 4 && tmp->token <= 8) || 
		((ft_strcmp(tmp->content, ">") || ft_strcmp(tmp->content, "<") 
		|| ft_strcmp(tmp->content, "|")) && ft_strlen(tmp->content) == 1))
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

int	skip_first_operator(t_lexer **list, char *line, int *i, int *j)
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
	while (line[*i] == '>' || line[*i] == '<' || line[*i] == '|')
		(*i)++;
	word = ft_strdupi(&line[*j], *i - *j);
	if (!ft_strlen(word))
		return (0);
	if (!add_node(list, word, UNCHECKED))
		return (-1);
	*j = (*i)++;
	return (1);
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
			if (i == 0)
			{
				if (line[i] == '|')
				{
					printf("syntax error!\n");
					return (0);
				}
				state = skip_first_operator(list, line, &i, &j);
			}
			else
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

int	specify_operator(char *word, e_token *token)
{
	if (!ft_strcmp(word, ">>"))
		*token = DOUBLE_RIGHT_REDIR;
	else if (!ft_strcmp(word, ">"))
		*token = RIGHT_REDIR;
	else if (!ft_strcmp(word, "<<"))
		*token = HEREDOC;
	else if (!ft_strcmp(word, "<"))
		*token = LEFT_REDIR;
	else if (!ft_strcmp(word, "|") && ft_strlen(word) == 1)
		*token = PIPE;
	else
	{
		printf("syntax error!\n");
		return (0);
	}
	return (1);
}