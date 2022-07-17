/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 21:19:04 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/17 20:18:53 by mmoumni          ###   ########.fr       */
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

void    begin_execution(t_cmds *cmds, t_envp **env)
{
    int     i;
    t_cmds  *temp;
    int		**pipes;
	int		pid;
	int		res;
	
    temp = cmds;
	pipes = two_dim_arr(how_many_pipes(cmds));
	i = 0;
	res = 0;
	if (!how_many_pipes(cmds))
	{
		int status;
		is_builtin(temp,&res);
		if (res)
		{
			pid = fork();
			if (pid == 0)
				run_command(temp, env, -1, pipes);
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
			{
				g_minishell.exit_status = WEXITSTATUS(status);
			}
			if (WIFSIGNALED(status))
			{
				g_minishell.exit_status = WTERMSIG(status) + 128;
			}
			if (g_minishell.exit_status == 131)
				write(1,"Quit: 3\n",9);
			waitpid(-1, NULL, 0);
		}
		else
		{
			run_command(temp, env, -1, pipes);
		}
	}
	else
	{
		run_pipe(pipes);
		while (temp != NULL)
		{
			pid = fork();
			if (pid == 0)
				run_command(temp, env, i, pipes);
			i++;
			temp = next_cmd(temp);
		}
		close_all_pipes(pipes);
		waitpid(pid, &g_minishell.exit_status, 0);
		waitpid(-1, NULL, 0);
	}
}

void	is_builtin(t_cmds *cmd, int *res)
{
	if (!ft_strcmp(cmd->argv->argv, "PWD") || !ft_strcmp(cmd->argv->argv, "pwd"))
		*res = 0;
	if (!ft_strcmp(cmd->argv->argv, "ECHO") || !ft_strcmp(cmd->argv->argv, "echo"))
		*res = 0;
	else if (!ft_strcmp(cmd->argv->argv, "EXPORT") || !ft_strcmp(cmd->argv->argv, "export"))
		*res = 0;
	else if (!ft_strcmp(cmd->argv->argv, "UNSET") || !ft_strcmp(cmd->argv->argv, "unset"))
		*res = 0;
	else if (!ft_strcmp(cmd->argv->argv, "ENV") || !ft_strcmp(cmd->argv->argv, "env"))
		*res = 0;
	else if (!ft_strcmp(cmd->argv->argv, "CD") || !ft_strcmp(cmd->argv->argv, "cd"))
		*res = 0;
	else if (!ft_strcmp(cmd->argv->argv, "EXIT") || !ft_strcmp(cmd->argv->argv, "exit"))
		*res = 0;
	else
		*res = 1;
}


void	run_builtin(t_cmds *cmd, t_envp **env)
{
	if (!ft_strcmp(cmd->argv->argv, "PWD") || !ft_strcmp(cmd->argv->argv, "pwd"))
		ft_pwd(conv_t_char_to_tab(cmd->argv));
	else if (!ft_strcmp(cmd->argv->argv, "ECHO") || !ft_strcmp(cmd->argv->argv, "echo"))
		ft_echo(&conv_t_char_to_tab(cmd->argv)[1]);
	else if (!ft_strcmp(cmd->argv->argv, "EXPORT") || !ft_strcmp(cmd->argv->argv, "export"))
		ft_export(env, cmd->argv);
	else if (!ft_strcmp(cmd->argv->argv, "UNSET") || !ft_strcmp(cmd->argv->argv, "unset"))
		ft_unset(env, cmd->argv->next);
	else if (!ft_strcmp(cmd->argv->argv, "ENV") || !ft_strcmp(cmd->argv->argv, "env"))
		ft_env(*env, cmd->argv);
	else if (!ft_strcmp(cmd->argv->argv, "CD") || !ft_strcmp(cmd->argv->argv, "cd"))
		ft_cd(env, cmd->argv);
	else if (!ft_strcmp(cmd->argv->argv, "EXIT") || !ft_strcmp(cmd->argv->argv, "exit"))
		ft_exit(cmd->argv);
}

void	run_command(t_cmds *cmds, t_envp **env, int i, int **pipes)
{
	t_cmds	*cmd;
	int		infile;
	int		outfile;
	int		in;
	int		out;

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	infile = 0;
	outfile = 1;
	cmd = cmds;
	trait_redirection(cmd, *env, &infile, &outfile);
	if (infile == 0)
	{
		if (i > 0 && i != 0)
		{
			close(pipes[i - 1][1]);
			dup2(pipes[i - 1][0], 0);
			close(pipes[i - 1][0]);
		}
	}
	else
	{
		dup2(infile, STDIN_FILENO);
	}
	if (outfile == 1)
	{
		if (i > 0 && pipes[i] != NULL)
		{
			close(pipes[i][0]);
			dup2(pipes[i][1], 1);
			close(pipes[i][1]);	
		}
	}
	else
		dup2(outfile, STDOUT_FILENO);
	close_all_pipes(pipes);
	execute_cmd(cmd, env);
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
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
		{
			if (access(temp->argv->argv, (F_OK)))
			{
				printf("minishell: %s: No such file or directory\n", temp->argv->argv);
				exit (EXIT_FAILURE);
			}
			*infile = open(temp->argv->argv, O_RDWR, 0644);
		}
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

void read_write_herdoc(int *fds, char *str)
{
	int	str_size;
	char *buff;

	str_size = ft_strlen(str);
	buff = (char *)malloc(sizeof(char) * (str_size + 1));
	write(fds[1], buff, str_size);
	close(fds[1]);
	buff[str_size] = '\0';
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
				exit (127);
		}
		else
		{
			run_builtin(cmd, env);
		}
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

