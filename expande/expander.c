/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 10:41:10 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/01 16:10:57 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/struct.h"
#include "../headers/builtins.h"
#include "../headers/minishell.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char	*extract_var(char *start)
{
	char	*end;
	char	*var_name;

	end = start;
	while (end[0] && (ft_isalpha(end[0]) || ft_isdigit(end[0])))
		end++;
	var_name = ft_strdupi(start, advanced_strlen(start, end));
	return (var_name);
}

int	ft_expand(char	**word, t_envp *env)
{
	t_envp	*var;
	char	*new_word;
	char	*start;
	char	*var_name;
	char	*dollar_sign;

	var_name = NULL;
	start = *word;
	dollar_sign = ft_strchr(*word, '$');
	new_word = ft_strdup("");
	while (dollar_sign[0])
	{
		if (between_quote(*word, dollar_sign, '\''))
		{
			var_name = extract_var(dollar_sign + 1);
			var = search_key(env, var_name);
			new_word = ft_strjoin(new_word, ft_strdupi(start, advanced_strlen(start, dollar_sign)));
			if (var)
				new_word = ft_strjoin(new_word, var->value);
			start += ft_strlen(var_name) + 1;
		}
		dollar_sign = ft_strchr(dollar_sign + 1, '$');
	}
	if (start[0])
		new_word = ft_strjoin(new_word, start);
	free(*word);
	*word = new_word;
	return (1);
}

// int	ft_expand_heredoc(char **word, t_envp *env)
// {}

// int	replace_null_var(char **word, char *dollar)
// {
// 	return (1);
// }

// int	replace_var(char **word, t_envp *env, char *dollar)
// {
// 	int		new_word_len;
// 	char	*new_word;

// 	// if (!env)
// 	// 	return (replace_null_var(word, dollar));
// 	new_word_len = ft_strlen(*word) - ft_strlen(env->key) + ft_strlen(env->value);
// 	new_word = (char *)malloc(sizeof(char) * new_word_len);
// 	if (!new_word)
// 		return (0);
// 	ft_strncpy(new_word, *word, advanced_strlen(*word, dollar));
// 	ft_strlcat(new_word, env->value, new_word_len);
// 	ft_strlcat(new_word, dollar + ft_strlen(env->key) + 1, new_word_len);
// 	return (1);
// }