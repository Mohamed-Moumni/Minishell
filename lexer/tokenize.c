/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-iaz <yait-iaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:26:52 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/06/29 12:34:20 by yait-iaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_char_counter(char *str, char ch)
{
	int n;
	int	i;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] == ch)
			n++;
		i++;
	}
	return (n);
}

// void	check_option(char *word, e_token *token)
// {
// 	int	i;

// 	i = 1;
// 	while (word[i])
// 	{
// 		if (word[i] != word[1])
// 			return ;
// 		i++;
// 	}
// 	*token = OPTION;
// }

// void	check_term(char **word, e_token *token)
// {
// 	char	*single_q;
// 	char	*double_q;

// 	single_q = ft_strchr(*word, '\'');
// 	double_q = ft_strchr(*word, '"');
// 	if (single_q < double_q)
// 	{
// 		remove_quote(word, '\'', ft_char_counter(*word, '\''));
// 		*token = SINGLE_QUOTE;
// 	}
// 	else if (single_q > double_q)
// 	{
// 		remove_quote(word, '"', ft_char_counter(*word, '"'));
// 		*token = DOUBLE_QUOTE;
// 	}
// 	if (*word[0] == '-')
// 		check_option(*word, token);
// }

// e_token	ft_tokenize(char **word)
// {
// 	e_token	token;

// 	if (!ft_strcmp(*word, ">"))
// 		token = RIGHT_REDIR;
// 	if (!ft_strcmp(*word, ">>"))
// 		token = DOUBLE_RIGHT_REDIR;
// 	if (!ft_strcmp(*word, "<"))
// 		token = LEFT_REDIR;
// 	if (!ft_strcmp(*word, "<<"))
// 		token = DOUBLE_LEFT_REDIR;
// 	if (!ft_strcmp(*word, "|"))
// 		token = PIPE;
// 	else
// 		token = WORD;
// 	return ((e_token)token);
// }
