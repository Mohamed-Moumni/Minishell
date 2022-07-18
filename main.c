/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:47:30 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/07/18 19:39:43 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/struct.h"
#include "./headers/minishell.h"
#include "./headers/builtins.h"

void	replace_content(t_lexer *node, int *fd)
{
	char	*line;
	char	*double_quote;
	char	*single_quote;

	if (!node)
		return ;
	double_quote = ft_strchr(node->content, '"');
	single_quote = ft_strchr(node->content, '\'');
	if (double_quote[0] || single_quote[0])
		node->token = SINGLE_QUOTE;
	write(1, "> ", 2);
	line = get_next_line(0);
	if (line == NULL)
	{
		g_minishell.exit_status = 0;
		return ;
	}
	node->content = hundle_quote(node->content, NULL, node);
	while (ft_strcmp(line, node->content))
	{
		line = ft_strjoin(line, "\n");
		close (fd[0]);
		write(fd[1], line, ft_strlen(line));
		write(1, "> ", 2);
		line = get_next_line(0);
		if (line == NULL)
		{
			g_minishell.exit_status = 0;
			return ;
		}
	}
	close(fd[1]);
}

int	adjust_heredoc(t_lexer *list)
{
	t_lexer	*node;
	int		end;
	int		pid;
	int		fd[2];
	char	*buff;

	node = list;
	while (node)
	{
		if (!ft_strcmp(node->content, "<<"))
		{
			pipe(fd);
			pid = fork();
			if (pid == 0)
				replace_content(node->next, fd);
			else
				g_minishell.herdoc = pid;
			wait(NULL);
			if (!g_minishell.herdoc)
				return (0);
			close(fd[1]);
			buff = malloc(sizeof(char) * MAX_INPUT);
			end = read(fd[0], buff, MAX_INPUT);
			buff[end] = '\0';
			close(fd[0]);
			free(node->next->content);
			node->next->content = buff;
		}
		node = node->next;
	}
	return (1);
}

void	free_tchar(t_char **tchar)
{
	t_char	*temp;
	t_char	*next;

	temp = *tchar;
	while (temp)
	{
		next = temp->next;
		free(temp);
		temp = next;	
	}
}

void	free_cmd_list(t_cmds **cmds)
{
	t_cmds	*temp;

	temp = *cmds;
	while (temp)
	{
		free_tchar(&temp->argv);
		temp = temp->next;
	}
}

void	free_lexer(t_lexer **lexer)
{
	t_lexer *temp;
	t_lexer	*next;
	
	temp = *lexer;
	while (temp)
	{
		next = temp->next;
		free(temp->content);
		temp = next;
	}	
}

void	set_gminishell(void)
{
	g_minishell.exit_status = 0;
	g_minishell.unset_path = 0;
	g_minishell.sh_level = 2;
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

 rl_getc_function = getc;
   rl_catch_signals = 0;
   rl_catch_sigwinch = 0;
	(void)av;
	(void)ac;
	rl_catch_signals = 0;
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
			exit (EXIT_SUCCESS);
		}
		add_history(read_line);
		if (!readline_valid(read_line))
		{
			list = get_lexer(read_line);
			if (list)
			{
				if (adjust_heredoc(list))
				{
					start_execution(list, &envp);
				}
			}
			// free_lexer(&list);
		}
		// free(read_line);
	}
	return (0);
}
