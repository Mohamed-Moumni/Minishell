/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:34:00 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/07/20 22:15:35 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/struct.h"
#include "../headers/minishell.h"
#include "../headers/builtins.h"

char	*hundle_quote(char	*word, t_envp **env, t_lexer *node)
{
	int		i;
	char	s;
	char	*new_word;

	i = 0;
	s = 0;
	if (!word)
		return (NULL);
	new_word = ft_strdupi("", 1);
	if (env)
		ft_expand(&word, env, node);
	while (word[i])
	{
		if (s == 0 && (word[i] == '\'' || word[i] == '"'))
			s = word[i++];
		if (word[i] == s)
			s = 0;
		else
			new_word = ft_strjoin(new_word, ft_strdupi(&word[i], 1));
		i++;
	}
	if (s != 0)
		return (printf("unmatched quote\n"), NULL);
	return (free(word), new_word);
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

int	ft_char_counter(char *str, char ch)
{
	int	n;
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
