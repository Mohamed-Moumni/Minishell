/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:34:00 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/07/20 15:11:59 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/struct.h"
#include "../headers/minishell.h"
#include "../headers/builtins.h"

char	*hundle_quote(char	*word, t_envp **env, t_lexer *node)
{
	int i;
    char s;
    char *new_word;

	i = 0;
	s = 0;
	if (!word)
		return (NULL);
	new_word = NULL;
	if (env)
		ft_expand(&word, env, node);
    while(word[i])
    {
        if (s == 0 && (word[i] == '\'' || word[i] == '"'))
            s = word[i++];
        if (word[i] == s)
            s = 0;
        else
		{
            new_word = ft_strjoin_ad(new_word, ft_strdupi(&word[i], 1), 3);
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
	free(word);
	return (new_word);
}
