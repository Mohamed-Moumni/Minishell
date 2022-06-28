/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:34:00 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/06/28 09:34:36 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/builtins.h"

char	*add_after_quote(char *quote_ad)
{
	char	*tmp;

	if (quote_ad[0] == 0)
	{
		printf("error! unmatched quote\n");
		return (NULL);
	}
	tmp = quote_ad + 1;
	while (tmp[0] && tmp[0] != ' ')
		tmp++;
	quote_ad = tmp - 1;
	return (quote_ad);
}

char	*double_quote(char **word, char *line, char *quote, char *start)
{
	char	*second_quote;

	second_quote = ft_strchr(quote + 1, '"');
	second_quote = add_after_quote(second_quote);
	if (!second_quote)
		return (NULL);
	*word = ft_substr(line, 0, advanced_strlen(start, second_quote) + 1);
	return (second_quote);
}

char	*single_quote(char **word, char *line, char *quote, char *start)
{
	char	*second_quote;

	second_quote = ft_strchr(quote + 1, '\'');
	second_quote = add_after_quote(second_quote);
	if (!second_quote)
		return (NULL);
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
		if (!start)
			return (NULL);
		return (start + 1);
	}
	return (start);
}
