/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:47:30 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/07/20 21:41:52 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/struct.h"
#include "./headers/minishell.h"
#include "./headers/builtins.h"

void	set_gminishell(void)
{
	g_minishell.exit_status = 0;
	g_minishell.unset_path = 0;
	g_minishell.herdoc = 0;
}

int	readline_valid(char *read_line)
{
	int	i;

	i = 0;
	while (read_line[i] && ft_isspace(read_line[i]))
		i++;
	if (!read_line[i])
		return (1);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_lexer		*list;
	t_envp		*envp;
	char		*read_line;

	(void)av;
	(void)ac;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	set_gminishell();
	envp = envp_to_list(env);
	while (1)
	{
		read_line = readline("minishell$ ");
		if (read_line == NULL)
		{
			g_minishell.exit_status = 0;
			printf("exit\n");
			exit (EXIT_SUCCESS);
		}
		add_history(read_line);
		if (!readline_valid(read_line))
		{
			list = get_lexer(read_line);
			if (list)
			{
				if (adjust_heredoc(&list))
					start_execution(list, &envp);
			}
		}
	}
	return (0);
}
