/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 10:07:54 by mmoumni           #+#    #+#             */
/*   Updated: 2022/06/28 16:06:37 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/builtins.h"

int	treat_word(t_cmds *cmds, t_lexer *node)
{
}

int start_execution(t_lexer *list)
{
	t_cmds	*cmds;
	t_lexer	*tmp;

	tmp = list;
	cmds = NULL;
	while (tmp)
	{
		if (tmp->token == 0)
			treat_word(cmds, tmp);
		tmp = tmp->next;
	}
}

void	run_pipe(t_cmds *cmds)
{
	char	**tab;
	char	**env;
	int		pid;
	
	if (pipe(cmds->fd) == -1)
		return ;
	if (cmds->prev == NULL)
	{
		pid = fork();
		if (pid == 0)
		{
				close (cmds->fd[0]);
				dup2 (cmds->fd[1], 1);
				close (cmds->fd[1]);
				expande(cmds->argv);
				tab = t_char_to_argv();
				env = env_list_to_tab();
				execve(tab[0], tab, env);
		}
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			close(cmds->prev->fd[1]);
			dupe2(cmds->prev->fd[0], 0);
			close(cmds->prev->fd[0]);
			close(cmds->fd[0]);
			dupe2(cmds->fd[1], 1);
			close(cmds->fd[1]);
			expande(cmds->argv);
			tab = t_char_to_argv();
			env = env_list_to_tab();
			execve(tab[0], tab, env);
		}
	}
	waitpid(pid, NULL, 0);
}

void	run_redirection(t_cmds *cmds)
{
	char	**tab;
	char	**env;
	int		pid;
	char	*buff;
	int		fd_file;

	if (cmds->prev == NULL)
	{
		expande(cmds->argv);
		tab = t_char_to_argv();
		env = env_list_to_tab();
		if (cmds->type == RIGHT_REDIR)
		{
			fd_file = open(tab[0], (O_CREAT |  O_WRONLY | O_TRUNC), 0644);
			if (fd_file == -1)
				return ;
			if (read (STDIN_FILENO, buff, 0) == -1)
				return ;
			if (write(fd_file, buff, 0) == -1)
				return ;
		}
		else if (cmds->type == DOUBLE_RIGHT_REDIR)
		{
			fd_file = open(tab[0], (O_CREAT &  O_WRONLY & O_APPEND), 0644);
			if (fd_file == -1)
				return ;
			if (read (STDIN_FILENO, buff, 0) == -1)
				return ;
			if (write(fd_file, buff, 0) == -1)
				return ;
		}
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (cmds->type == RIGHT_REDIR)
			{
				fd_file = open(tab[0], (O_CREAT &  O_WRONLY & O_TRUNC), 0644);
				if (fd_file == -1)
					return ;		
				close (cmds->prev->fd[1]);
				if (read(cmds->prev->fd[0], buff, 0) == -1)
					return ;
				if (write(fd_file, buff, 0) == -1)
					return ;
			}
			else if (cmds->type == DOUBLE_RIGHT_REDIR)
			{
				fd_file = open(tab[0], (O_CREAT &  O_WRONLY & O_APPEND), 0644);
				if (fd_file == -1)
					return ;
				close (cmds->prev->fd[1]);
				if (read (cmds->prev->fd[0], buff, 0) == -1)
					return ;
				if (write(fd_file, buff, 0) == -1)
					return ;
			}
		}
		waitpid (pid, NULL, 0);
	}
}