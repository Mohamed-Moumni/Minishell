/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-iaz <yait-iaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:26:52 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/06/12 15:30:26 by yait-iaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quote(char **word, char quote)
{
	int		i;
	int		j;
	int		word_len;
	char	*new_world;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = *word;
	word_len = ft_strlen(*word) - 1;
	new_world = malloc(sizeof(char) * word_len);
	while (tmp[i])
	{
		if (tmp[i] != quote)
			new_world[j++] = tmp[i];
		i++;
	}
	new_world[j] = 0;
	free(*word);
	*word = new_world;
}

void	check_option(char *word, e_token *token)
{
	int	i;

	i = 1;
	while (word[i])
	{
		if (word[i] != word[1])
			return ;
		i++;
	}
	*token = OPTION;
}

void	check_term(char **word, e_token *token)
{
	char	*single_q;
	char	*double_q;

	single_q = ft_strchr(*word, '\'');
	double_q = ft_strchr(*word, '"');
	if (single_q < double_q)
	{
		remove_quote(word, '\'');
		*token = SINGLE_QUOTE;
	}
	else if (single_q > double_q)
	{
		remove_quote(word, '"');
		*token = DOUBLE_QUOTE;
	}
	if (*word[0] == '-')
		check_option(*word, token);
}

e_token	ft_tokenize(char **word)
{
	e_token	token;

	if ((ft_strchr(*word, '"')[0] || ft_strchr(*word, '\'')[0]))
		check_term(word, &token);
	else if (!ft_strcmp(*word, ">") || !ft_strcmp(*word, ">>") \
		|| !ft_strcmp(*word, "<") || !ft_strcmp(*word, "<<"))
		token = OPERATOR;
	else if (!ft_strcmp(*word, "|"))
		token = PIPE;
	else
		token = WORD;
	return ((e_token)token);
}
