/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-iaz <yait-iaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:34:00 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/06/11 15:11:47 by yait-iaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_after_quote(char *line, char *quote_ad, char quote)
{
	char	*tmp;
	char	*line_rest;

	while (quote_ad == 0)
	{
		line_rest = readline(">>");
		line = ft_strjoin(line, line_rest);
		quote_ad = ft_strchr(line, quote);
	}
	tmp = quote_ad + 1;
	while (tmp[0] && tmp[0] != ' ')
		tmp++;
	if (tmp[0])
		quote_ad = tmp - 1;
	else
		quote_ad = tmp;
	return (quote_ad);
}

char	*single_quote(char **word, char *line, char *quote, char *start)
{
	char	*second_quote;

	second_quote = ft_strchr(quote + 1, '\'');
	second_quote = add_after_quote(line, second_quote, '\'');
	*word = ft_substr(line, 0, advanced_strlen(start, second_quote) + 1);
	return (second_quote);
}

char	*double_quote(char **word, char *line, char *quote, char *start)
{
	char	*second_quote;

	second_quote = ft_strchr(quote + 1, '"');
	second_quote = add_after_quote(line, second_quote, '"');
	*word = ft_substr(line, 0, advanced_strlen(start, second_quote) + 1);
	return (second_quote);
}

char	*add_before_quote(char *quote, char *line)
{
	char	*tmp;

	tmp = quote - 1;
	while (tmp[0] != ' ' && tmp != line)
		tmp--;
	if (tmp != line)
		quote = tmp + 1;
	else
		quote = line;
	return (quote);
}

char	*quote_handle(char **word, char *line, char *start)
{
	char	*start_quote;
	char	*double_q;
	char	*single_q;

	double_q = ft_strchr(*word, '"');
	single_q = ft_strchr(*word, '\'');
	if (double_q[0] || single_q[0])
	{
		if (double_q < single_q)
		{
			double_q = ft_strchr(line, '"');
			start_quote = add_before_quote(double_q, line);
			start = double_quote(word, line, double_q, start_quote);
		}
		else
		{
			single_q = ft_strchr(line, '\'');
			start_quote = add_before_quote(single_q, line);
			start = single_quote(word, line, single_q, start_quote);
		}
		return (start + 1);
	}
	return (start);
}
