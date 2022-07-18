/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 10:41:10 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/18 20:59:33 by Ma3ert           ###   ########.fr       */
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
	if (end[0] == '?')
	{
		end++;
		return (ft_strdupi(start, advanced_strlen(start, end)));
	}
	while (end[0] && (ft_isalpha(end[0]) || ft_isdigit(end[0]) || end[0] == '_'))
		end++;
	var_name = ft_strdupi(start, advanced_strlen(start, end));
	return (var_name);
}

int	ft_expand(char	**word, t_envp **env, t_lexer *node)
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
	while (dollar_sign[0] && dollar_sign[1])
	{
		if (node->token != SINGLE_QUOTE && between_quote(*word, dollar_sign, '\''))
		{
			var_name = extract_var(dollar_sign + 1);
			if (!ft_strcmp(var_name, "?"))
				var = NULL;
			else
				var = search_key(*env, var_name);
			new_word = ft_strjoin(new_word, ft_strdupi(start, advanced_strlen(start, dollar_sign)));
			if (var)
				new_word = ft_strjoin(new_word, var->value);
			else if (!ft_strcmp(var_name, "?"))
				new_word = ft_strjoin(new_word, ft_itoa(g_minishell.exit_status));
			start = dollar_sign + ft_strlen(var_name) + 1;
		}
		dollar_sign = ft_strchr(dollar_sign + 1, '$');
	}
	if (start[0])
		new_word = ft_strjoin(new_word, start);
	free(*word);
	*word = new_word;
	return (1);
}