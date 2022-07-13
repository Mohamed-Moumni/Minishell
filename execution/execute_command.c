/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 21:19:04 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/13 14:56:35 by mmoumni          ###   ########.fr       */
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


void    begin_execution(t_cmds *cmds, t_envp *env)
{
    int     i;
    t_cmds  *temp;
    int		**pipes;
	int		pid;

    temp = cmds;
	pipes = two_dim_arr(how_many_pipes(cmds));
	i = 0;
	if (!pipes)
	{
		pid = fork();
		if (pid == 0)
			run_command(temp, env, -1, pipes);
	}
	else
	{
		run_pipe(pipes);
		while (temp != NULL)
		{
			pid = fork();
			if (pid == 0)
			{
				run_command(temp, env, i, pipes);
			}
			i++;
			temp = next_cmd(temp);
		}
		close_all_pipes(pipes);
		waitpid(pid, NULL,0);
		waitpid(-1, NULL, 0);
	}
}

void	run_command(t_cmds *cmds, t_envp *env, int i, int **pipes)
{
	t_cmds	*cmd;
	int		infile;
	int		outfile;

	infile = 0;
	outfile = 1;
	// if (cmds->type == WORD || cmds->type == PIPE)
	// {
		cmd = cmds;
		trait_redirection(cmd->next, env, &infile, &outfile);
		if (infile == 0)
		{
			if (i != 0)
			{
				close(pipes[i - 1][1]);
				dup2(pipes[i - 1][0], 0);
				close(pipes[i - 1][0]);
			}
		}
		else
			dup2(infile, 0);
		if (outfile == 1)
		{
			if (pipes[i] != NULL)
			{
				close(pipes[i][0]);
				dup2(pipes[i][1], 1);
				close(pipes[i][1]);	
			}
		}
		else
			dup2(outfile, 1);
		close_all_pipes(pipes);
		execute_cmd(cmd, env);
	// }
}

void	trait_redirection(t_cmds *cmds, t_envp *env, int *infile, int *outfile)
{
	t_cmds	*temp;
	int		fds[2];
	(void)env;

	temp = cmds;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == RIGHT_REDIR)
			*outfile = open(temp->argv->argv, O_CREAT | O_TRUNC | O_RDWR, 0644);
		else if (temp->type == DOUBLE_RIGHT_REDIR)
			*outfile = open(temp->argv->argv, O_CREAT | O_APPEND | O_RDWR, 0644);
		else if (temp->type == LEFT_REDIR)
			*infile = open(temp->argv->argv, O_RDWR, 0644); // after test append the case that file doesnt exist
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

void	execute_cmd(t_cmds *cmd, t_envp *env)
{
	char **args;
	char **envp;

	args = conv_t_char_to_tab(cmd->argv);
	envp = list_to_envp(env);
	execve(cmd->argv->argv, args, envp);
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