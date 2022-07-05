/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:47:30 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/07/04 11:06:37 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/struct.h"
#include "./headers/minishell.h"
#include "./headers/builtins.h"

void	replace_content(t_lexer *node)
{
	char	*line;
	char	*double_quote;
	char	*single_quote;
	char	*new_content;

	if (!node)
		return ;
	double_quote = ft_strchr(node->content, '"');
	single_quote = ft_strchr(node->content, '\'');
	if (double_quote[0] || single_quote[0])
		node->token = SINGLE_QUOTE;
	line = readline("> ");
	node->content = hundle_quote(node->content, NULL, node);
	new_content = ft_strdupi("", 0);
	while (ft_strcmp(line, node->content))
	{
		line = ft_strjoin(line, "\n");
		new_content = ft_strjoin(new_content, line);
		line = readline("> ");
	}
	free(node->content);
	node->content = new_content;
}

void	adjust_heredoc(t_lexer *list)
{
	t_lexer	*node;

	node = list;
	while (node)
	{
		if (!ft_strcmp(node->content, "<<"))
			replace_content(node->next);
		node = node->next;
	}
}


void	create_env_export(t_envp **envp, t_export **export, char **env)
{
	
	if (!(*env))
	{
		g_minishell.sh_level = 1;
		*envp = without_env();
		*export = without_export();
	}
	else{	
		g_minishell.sh_level = 2;
		*envp = envp_to_list(env);
		*export = env_to_expo_list(env);
	}
}
int	main(int ac, char **av, char **env)
{
	t_lexer		*list;
	t_envp		*env_list;
	// t_export	*export_list;

	(void)av;
	(void)ac;
	env_list = envp_to_list(env);
	while (1)
	{
		list = get_lexer(readline("@minishell >> "));
		if (list)
		{
			adjust_heredoc(list);
			start_execution(list, env_list);
		}
	}
	return (0);
}