/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:47:30 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/07/20 22:59:28 by mmoumni          ###   ########.fr       */
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
	g_minishell.child = 0;
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
		exit (EXIT_SUCCESS);
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
			close(fd[1]);
			exit (EXIT_SUCCESS);
		}
	}
	close(fd[1]);
	exit(EXIT_SUCCESS);
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

int	main(int ac, char **av, char **env)
{
	t_lexer		*list;
	t_envp		*envp;
	char		*read_line;
	char		*line;

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
			line = ft_strdup(read_line);
			list = get_lexer(line);
			if (list)
			{
				if (adjust_heredoc(list))
					start_execution(list, &envp);
			}
			free_lexer(&list);
		}
		free (read_line);
	}
	free_envp_list(&envp);
	free(read_line);
	return (0);
}
