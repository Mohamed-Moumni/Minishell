/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:20:29 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/21 08:46:41 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/builtins.h"
#include "../headers/minishell.h"
#include "../headers/struct.h"

t_cmds	*next_cmd(t_cmds *cmds)
{
	t_cmds	*temp;

	temp = cmds;
	if (temp->type == WORD || temp->type == PIPE)
		temp = temp->next;
	while (temp && (temp->type != WORD && temp->type != PIPE))
		temp = temp->next;
	return (temp);
}

void	one_cmd(t_cmds *cmds, t_envp **env)
{
	int		res;
	t_cmds	*temp;
	int		pid;

	res = 0;
	temp = cmds;
	is_builtin(temp, &res);
	if (res)
	{
		pid = fork();
		if (pid == 0)
		{
			run_one_cmd(temp, env);
			exit(EXIT_SUCCESS);
		}
		else
			g_minishell.child = pid;
		waitpid(pid, &g_minishell.exit_status, 0);
		get_exit_status(g_minishell.exit_status);
	}
	else
		run_one_cmd(temp, env);
}

void	mutliple_cmds(t_cmds *cmds, t_envp **env, int **pipes)
{
	t_cmds	*temp;
	int		pid;
	int		i;

	i = 0;
	temp = cmds;
	run_pipe(pipes);
	while (temp != NULL)
	{
		pid = fork();
		if (pid == 0)
		{
			run_command(temp, env, i, pipes);
			exit(EXIT_SUCCESS);
		}
		g_minishell.child = pid;
		i++;
		temp = next_cmd(temp);
	}
	close_all_pipes(pipes);
	waitpid(pid, &g_minishell.exit_status, 0);
	while (waitpid(-1, NULL, 0) > 0)
		;
	get_exit_status(g_minishell.exit_status);
}

int	open_left_redir(t_cmds *cmds)
{
	t_cmds	*temp;
	int		fd;

	temp = cmds;
	if (access(temp->argv->argv, (F_OK)))
	{
		printf("minishell: %s: No such file or directory\n", temp->argv->argv);
		exit (EXIT_FAILURE);
	}
	fd = open(temp->argv->argv, O_RDWR, 0644);
	return (fd);
}

void	is_builtin(t_cmds *cmd, int *res)
{
	char	*temp;

	temp = cmd->argv->argv;
	if (!ft_strcmp(temp, "PWD") || !ft_strcmp(temp, "pwd"))
		return ;
	if (!ft_strcmp(temp, "ECHO") || !ft_strcmp(temp, "echo"))
		return ;
	if (!ft_strcmp(temp, "EXPORT") || !ft_strcmp(temp, "export"))
		return ;
	if (!ft_strcmp(temp, "UNSET") || !ft_strcmp(temp, "unset"))
		return ;
	if (!ft_strcmp(temp, "ENV") || !ft_strcmp(temp, "env"))
		return ;
	if (!ft_strcmp(temp, "CD") || !ft_strcmp(temp, "cd"))
		return ;
	if (!ft_strcmp(temp, "EXIT") || !ft_strcmp(temp, "exit"))
		return ;
	else
		*res = 1;
}
