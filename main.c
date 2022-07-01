/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:47:30 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/07/01 16:02:45 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/struct.h"
#include "./headers/minishell.h"
#include "./headers/builtins.h"

void	replace_content(t_lexer *node)
{
	char	*line;
	char	*new_content;

	if (!node)
		return ;
	line = readline("> ");
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

int	main(int ac, char **av, char **env)
{
	t_lexer	*list;
	t_envp	*env_list;

	env_list = envp_to_list(env);
	// if (ac > 1)
	// 	return (0);
	(void)ac;
	(void)av;
	// (void)env;
	while (1)
	{
		list = get_lexer(readline("@minishell >> "));
	// // 	adjust_heredoc(list);
		if (list)
			print_lexer(list);
		start_execution(list, env_list);
	}
	return (0);
}
