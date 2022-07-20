/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 10:41:10 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/20 22:57:57 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/struct.h"
#include "../headers/builtins.h"
#include "../headers/minishell.h"

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
	while (end[0] && (ft_isalpha(end[0]) || ft_isdigit(end[0]) \
		|| end[0] == '_'))
		end++;
	var_name = ft_strdupi(start, advanced_strlen(start, end));
	return (var_name);
}

t_envp	*treat_var_name(t_envp *env, char *var_name)
{
	t_envp	*var;

	var = NULL;
	if (!ft_strcmp(var_name, "?"))
		var = NULL;
	else
		var = search_key(env, var_name);
	return (var);
}

char	*treat_var(t_envp *var, char *new_word, char *var_name)
{
	if (var)
		new_word = ft_strjoin(new_word, var->value);
	else if (!ft_strcmp(var_name, "?"))
		new_word = ft_strjoin(new_word, ft_itoa(g_minishell.exit_status));
	return (new_word);
}

char	*expand_in(char **var, char **start, char **dollar_sign, char *word)
{
	*var = NULL;
	*start = word;
	*dollar_sign = ft_strchr(word, '$');
	return (ft_strdup(""));
}

int	ft_expand(char	**word, t_envp **env, t_lexer *node)
{
	t_envp	*var;
	char	*new_word;
	char	*start;
	char	*var_name;
	char	*dollar;

	new_word = expand_in(&var_name, &start, &dollar, *word);
	while (dollar[0] && dollar[1])
	{
		if (node->token != SINGLE_QUOTE && between_quote(*word, dollar, '\''))
		{
			var_name = extract_var(dollar + 1);
			var = treat_var_name(*env, var_name);
			new_word = ft_strjoin(new_word, ft_strdupi(start, \
				advanced_strlen(start, dollar)));
			new_word = treat_var(var, new_word, var_name);
			start = dollar + ft_strlen(var_name) + 1;
		}
		dollar = ft_strchr(dollar + 1, '$');
	}
	if (start[0])
		new_word = ft_strjoin(new_word, start);
	free(*word);
	*word = new_word;
	return (free(var_name), 1);
}
