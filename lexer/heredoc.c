/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 19:22:10 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/07/21 15:57:00 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/struct.h"
#include "../headers/minishell.h"
#include "../headers/builtins.h"

void	write_on_pipe(t_lexer *node, char *line, int *fd)
{
	while (ft_strcmp(line, node->content))
	{
		line = ft_strjoin_ad(line, "\n", 1);
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
}

void	replace_content(t_lexer *node, int *fd)
{
	char	*line;

	if (!node)
		return ;
	write(1, "> ", 2);
	line = get_next_line(0);
	if (line == NULL)
		exit (EXIT_SUCCESS);
	node->content = hundle_quote(node->content, NULL, node);
	write_on_pipe(node, line, fd);
	close(fd[1]);
	exit(EXIT_SUCCESS);
}

int	adjust_content(t_lexer *node, int *fd)
{
	int		pid;
	char	*buff;
	int		end;

	if (!ft_strcmp(node->content, "<<"))
	{
		pipe(fd);
		set_token(node->next);
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
	return (1);
}

void	adjust_lexer(t_lexer **list)
{
	char	*space;
	char	*start;
	char	*new_content;
	t_lexer	*node;

	start = NULL;
	new_content = NULL;
	node = NULL;
	if ((*list)->token == HEREDOC)
	{
		node = (*list)->next;
		start = node->content;
		space = ft_strchr(start, ' ');
		if (space[0])
		{
			new_content = ft_strdupi(start, advanced_strlen(start, space));
			start = space + 1;
			add_front_lexer(list, ft_strdup(start), WORD);
		}
		free(node->content);
		node->content = new_content;
	}
}

int	adjust_heredoc(t_lexer **list)
{
	t_lexer	*node;
	int		fd[2];

	node = *list;
	adjust_lexer(list);
	while (node)
	{
		if (!adjust_content(node, fd))
			return (0);
		node = node->next;
	}
	return (1);
}
