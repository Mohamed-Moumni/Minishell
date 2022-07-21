/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 10:41:10 by mmoumni           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/07/20 22:57:57 by Ma3ert           ###   ########.fr       */
=======
/*   Updated: 2022/07/20 15:28:15 by mmoumni          ###   ########.fr       */
>>>>>>> 0cb64a4ac40e9ff27622284eedba035955a3e2f3
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

<<<<<<< HEAD
	new_word = expand_in(&var_name, &start, &dollar, *word);
	while (dollar[0] && dollar[1])
=======
	var_name = NULL;
	start = *word;
	dollar_sign = ft_strchr(*word, '$');
	new_word = NULL;
	while (dollar_sign[0] && dollar_sign[1])
>>>>>>> 0cb64a4ac40e9ff27622284eedba035955a3e2f3
	{
		if (node->token != SINGLE_QUOTE && between_quote(*word, dollar, '\''))
		{
<<<<<<< HEAD
			var_name = extract_var(dollar + 1);
			var = treat_var_name(*env, var_name);
			new_word = ft_strjoin(new_word, ft_strdupi(start, \
				advanced_strlen(start, dollar)));
			new_word = treat_var(var, new_word, var_name);
			start = dollar + ft_strlen(var_name) + 1;
=======
			var_name = extract_var(dollar_sign + 1);
			if (!ft_strcmp(var_name, "?"))
				var = NULL;
			else
				var = search_key(*env, var_name);
			new_word = ft_strjoin_ad(new_word, ft_strdupi(start, advanced_strlen(start, dollar_sign)), 3);
			if (var)
				new_word = ft_strjoin_ad(new_word, var->value, 1);
			else if (!ft_strcmp(var_name, "?"))
				new_word = ft_strjoin_ad(new_word, ft_itoa(g_minishell.exit_status), 3);
			start = dollar_sign + ft_strlen(var_name) + 1;
>>>>>>> 0cb64a4ac40e9ff27622284eedba035955a3e2f3
		}
		dollar = ft_strchr(dollar + 1, '$');
	}
	if (start[0])
		new_word = ft_strjoin_ad(new_word, start, 1);
	free(*word);
	*word = new_word;
	return (free(var_name), 1);
<<<<<<< HEAD
}
=======
}
>>>>>>> 0cb64a4ac40e9ff27622284eedba035955a3e2f3
