/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 21:19:04 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/20 09:17:48 by mmoumni          ###   ########.fr       */
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

void	get_exit_status(int status)
{
	if (WIFEXITED(status))
		g_minishell.exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		g_minishell.exit_status = WTERMSIG(status) + 128;
	if (g_minishell.exit_status == 131)
		write(1, "Quit: 3\n", 9);
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
		i++;
		temp = next_cmd(temp);
	}
	close_all_pipes(pipes);
	waitpid(pid, &g_minishell.exit_status, 0);
	while (waitpid(-1, NULL, 0) > 0)
		;
	get_exit_status(g_minishell.exit_status);
}

void	begin_execution(t_cmds *cmds, t_envp **env)
{
	t_cmds	*temp;
	int		**pipes;

	temp = cmds;
	pipes = two_dim_arr(how_many_pipes(cmds));
	if (!how_many_pipes(cmds))
		one_cmd(cmds, env);
	else
		mutliple_cmds(cmds, env, pipes);
	free_tab((void *)pipes);
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

void	run_builtin(t_cmds *cmd, t_envp **env)
{
	char	*temp;

	temp = cmd->argv->argv;
	if (!ft_strcmp(temp, "PWD") || !ft_strcmp(temp, "pwd"))
		ft_pwd(conv_t_char_to_tab(cmd->argv));
	else if (!ft_strcmp(temp, "ECHO") || !ft_strcmp(temp, "echo"))
		ft_echo(&conv_t_char_to_tab(cmd->argv)[1]);
	else if (!ft_strcmp(temp, "EXPORT") || !ft_strcmp(temp, "export"))
		ft_export(env, cmd->argv);
	else if (!ft_strcmp(temp, "UNSET") || !ft_strcmp(temp, "unset"))
		ft_unset(env, cmd->argv->next);
	else if (!ft_strcmp(temp, "ENV") || !ft_strcmp(temp, "env"))
		ft_env(*env, cmd->argv);
	else if (!ft_strcmp(temp, "CD") || !ft_strcmp(temp, "cd"))
		ft_cd(env, cmd->argv);
	else if (!ft_strcmp(temp, "EXIT") || !ft_strcmp(temp, "exit"))
		ft_exit(cmd->argv);
}

void	run_one_cmd(t_cmds *cmds, t_envp **env)
{
	t_cmds		*cmd;
	int			infile;
	int			outfile;
	int			in;
	int			out;

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	infile = 0;
	outfile = 1;
	cmd = cmds;
	trait_redirection(cmd,*env, &infile, &outfile);
	if (infile != 0)
		dup2(infile, STDIN_FILENO);
	if (outfile != 1)
		dup2(outfile, STDOUT_FILENO);
	execute_cmd(cmd, env);
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
}

void	run_command(t_cmds *cmds, t_envp **env, int i, int **pipes)
{
	t_cmds	*cmd;
	int		infile;
	int		outfile;

	infile = 0;
	outfile = 1;
	cmd = cmds;
	trait_redirection(cmd, *env, &infile, &outfile);
	if (infile == 0)
	{
		if (i > 0)
			dup2(pipes[i - 1][0], 0);
	}
	else
		dup2(infile, STDIN_FILENO);
	if (outfile == 1)
	{
		if (pipes[i] != NULL)
			dup2(pipes[i][1], 1);
	}
	else
		dup2(outfile, STDOUT_FILENO);
	close_all_pipes(pipes);
	execute_cmd(cmd, env);
}

void	trait_redirection(t_cmds *cmds, t_envp *env, int *infile, int *outfile)
{
	t_cmds	*temp;
	int		fds[2];

	(void)env;
	temp = cmds;
	if (temp->type == PIPE || temp->type == WORD)
		temp = temp->next;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == RIGHT_REDIR)
			*outfile = open(temp->argv->argv, O_CREAT | O_TRUNC | O_RDWR, 0644);
		else if (temp->type == DOUBLE_RIGHT_REDIR)
			*outfile = open(temp->argv->argv, O_CREAT | O_APPEND | O_RDWR, 0644);
		else if (temp->type == LEFT_REDIR)
			*infile = open_left_redir(cmds);
		else if (temp->type == HEREDOC)
		{
			pipe(fds);
			write(fds[1], temp->argv->argv, ft_strlen(temp->argv->argv));
			close(fds[1]);
			*infile = fds[0];
		}
		temp = temp->next;
	}
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

void	execute_cmd(t_cmds *cmd, t_envp **env)
{
	char	**args;
	char	**envp;
	int		res;
	char	*command;

	res = 0;
	if (cmd->type == WORD || cmd->type == PIPE)
	{
		is_builtin(cmd, &res);
		if (res)
		{
			command = cmd_valid(cmd->argv->argv);
			if (command)
			{
				args = conv_t_char_to_tab(cmd->argv);
				envp = list_to_envp(*env);
				args[0] = command;
				if (execve(args[0], args, envp) == -1)
					exit (EXIT_FAILURE);
			}
			else
				exit (g_minishell.exit_status);
		}
		else
			run_builtin(cmd, env);
	}
}

void	run_pipe(int **pipes)
{
	int	i;

	i = 0;
	while (pipes[i])
	{
		pipe(pipes[i]);
		i++;
	}
}

void	close_all_pipes(int **pipes)
{
	int	i;

	i = 0;
	while (pipes[i])
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}
