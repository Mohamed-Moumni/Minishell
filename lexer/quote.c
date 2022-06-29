/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-iaz <yait-iaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:34:00 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/06/29 20:18:57 by yait-iaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/builtins.h"

char	*hundle_quote(char	*word)
{
	int i;
    char s;
    char *new_word;

	i = 0;
	s = 0;
	if (!word)
		return (NULL);
	new_word = ft_strdupi("", 1);
    while(word[i])
    {
        if (s == 0 && (word[i] == '\'' || word[i] == '"'))
            s = word[i++];
        if (word[i] == s)
            s = 0;
        else
		{
            new_word = ft_strjoin(new_word, ft_strdupi(&word[i], 1));
			if (!new_word)
				return (NULL);
		}
        i++;
    }
	if (s != 0)
	{
		printf("unmatched quote\n");
		return (NULL);
	}
	return (new_word);
}

// char	*add_after_quote(char *quote_ad)
// {
// 	char	*tmp;

// 	if (quote_ad[0] == 0)
// 	{
// 		printf("error! unmatched quote\n");
// 		return (NULL);
// 	}
// 	tmp = quote_ad + 1;
// 	while (tmp[0] && tmp[0] != ' ')
// 		tmp++;
// 	quote_ad = tmp - 1;
// 	return (quote_ad);
// }

// char	*add_before_quote(char *quote, char *line)
// {
// 	char	*tmp;

// 	tmp = quote - 1;
// 	while (tmp[0] != ' ' && tmp != line)
// 		tmp--;
// 	if (tmp != line)
// 		quote = tmp + 1;
// 	else
// 		quote = line;
// 	return (quote);
// }

// char	*quote_handle(char **word, char *line, char *start)
// {
// 	char	*start_quote;
// 	char	*double_q;
// 	char	*single_q;

// 	double_q = ft_strchr(*word, '"');
// 	single_q = ft_strchr(*word, '\'');
// 	if (double_q[0] || single_q[0])
// 	{
// 		if (double_q < single_q)
// 		{
// 			printf("word: %s\n", *word);
// 			double_q = ft_strchr(line, '"');
// 			start_quote = add_before_quote(double_q, line);
// 			start = double_quote(word, line, double_q, start_quote);
// 			remove_quote(word, *double_q, ft_char_counter(*word, *double_q));
// 		}
// 		else
// 		{
// 			single_q = ft_strchr(line, '\'');
// 			start_quote = add_before_quote(single_q, line);
// 			start = single_quote(word, line, single_q, start_quote);
// 			remove_quote(word, *single_q, ft_char_counter(*word, *double_q));
// 		}
// 		if (!start)
// 			return (NULL);
// 		return (start + 1);
// 	}
// 	return (start);
// }
