/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 21:19:04 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/12 19:10:52 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/builtins.h"
#include "../headers/minishell.h"
#include "../headers/struct.h"

// t_exec	*execute_node(t_cmds *cmd, t_cmds *file, int inf, int outf)
// {
// 	t_exec	*node;

// 	node = (t_exec *)malloc(sizeof(t_exec));
// 	if (!node)
// 		return (NULL);
// 	node->type = cmd->type;
// 	node->infile = inf;
// 	node->outfile = outf;
// 	node->file = file->argv;
// 	node->argv = cmd->argv;
// 	node->next = NULL;
// 	return (node);
// }

// t_exec	*last_exec(t_exec *exec)
// {
// 	t_exec *temp;

// 	temp = exec;
// 	while (temp->next)
// 	{
// 		temp = temp->next;
// 	}
// 	return (temp);
// }

// void	exec_add_back(t_exec **exec, t_exec *new)
// {
// 	t_exec	*last;

// 	if (*exec == NULL)
// 		*exec = new;
// 	else
// 	{
// 		last = last_exec(*exec);
// 		last->next = new;		
// 	}
// }

// void	add_command(t_exec **exec, t_cmds *cmd, t_cmds *file)
// {
// 	if (file->type == LEFT_REDIR)
// 	{
// 		exec_add_back(exec, execute_node(cmd, file, 2, 1));
// 	}
// 	else if (file->type == RIGHT_REDIR)
// 	{
// 		exec_add_back(exec, execute_node(cmd, file, 0, 2));
// 	}
// 	else
// 		exec_add_back(exec, execute_node(cmd, file, 0, 3));
// }

// int	open_file(char *path, e_token token)
// {
// 	int	fd;

// 	if (token == RIGHT_REDIR)
// 		fd = open(path, O_RDWR | O_TRUNC | O_CREAT, 0644);
// 	if (token == DOUBLE_RIGHT_REDIR)
// 		fd = open (path, O_RDWR | O_APPEND | O_CREAT, 0644);
// 	return (fd);
// }

// int	file_exist(char *path)
// {
// 	int	file;

// 	file = access(path, R_OK & F_OK);
// 	return (file);
// }

// t_cmds	*check_redirection(t_exec **exec, t_cmds *cmd, int **pipe, int i)
// {
// 	t_cmds	*temp;
// 	t_cmds	*last;
// 	int		fd;
// 	int		file;
// 	t_cmds	*command;

// 	(void)i;
// 	(void)pipe;
// 	temp = cmd;
// 	while (temp && temp->type != PIPE)
// 	{
// 		if (temp->type == RIGHT_REDIR || temp->type == DOUBLE_RIGHT_REDIR)
// 		{
// 			fd = open_file(temp->argv->argv, temp->type);
// 			if (fd == -1)
// 			{
// 				return (temp);
// 			}
// 		}
// 		else if (temp->type == LEFT_REDIR)
// 		{
// 			file = file_exist(temp->argv->argv);
// 			if (fd == -1)
// 				return (temp);
// 		}
// 		if (temp->type == WORD || temp->type == PIPE)
// 			command = temp;
// 		last = temp;
// 		temp = temp->next;
// 	}
// 	add_command(exec, command, last);
// 	return (temp);
// }

// int	**pipes_allocat(int n)
// {
// 	int	i;
// 	int	**pipes;
	
// 	i = 0;
// 	pipes = (int **)malloc(sizeof(int *) * n);
// 	while (i < n)
// 	{
// 		pipes[i] = (int *)malloc(sizeof(int) * 2);
// 		i++;	
// 	}
// 	return (pipes);
// }

// void	run_pipes(int **pipes, int n)
// {
// 	int i;

// 	i = 0;
// 	while (i < n)
// 	{
// 		pipe(pipes[i]);
// 		i++;
// 	}	
// }

// void	print_exec(t_exec *exec)
// {
// 	t_exec *temp;

// 	temp = exec;
// 	while (temp)
// 	{
// 		printf("%d -- %s -- %s [%d ** %d]\n",temp->type, temp->argv->argv, temp->file->argv, temp->infile, temp->outfile);
// 		temp = temp->next;
// 	}
// }
// t_exec	*cmds_to_exec(t_cmds *cmds)
// {
// 	t_cmds	*temp;
// 	t_exec	*exec;
// 	int		**pipes;
// 	int		i;

// 	i = 0;
// 	temp = cmds;
// 	pipes = NULL;
// 	exec = NULL;
// 	// pipes = pipes_allocat(how_many_pipes(cmds));
// 	// run_pipes(pipes, how_many_pipes(cmds));
// 	while (temp)
// 	{
// 		while (temp && temp->type != PIPE)
// 		{
// 			temp = check_redirection(&exec, temp, pipes, i);
// 			// if (temp && temp->type != PIPE)
// 			// {
// 			// 	printf("Error\n");
// 			// 	break ;
// 			// }	
// 		}
// 		if (temp && temp->type == PIPE)
// 			temp = temp->next;
// 	}
// 	return(exec);
// }

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
			waitpid(pid, NULL, 0);
			i++;
			temp = next_cmd(temp);
		}
		i = 0;
		while (pipes[i])
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
			i++;
		}
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
		// printf("[[[%s]]]\n",cmd->argv->argv);
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
				close_fds(pipes, i);
				close(pipes[i][0]);
				dup2(pipes[i][1], 1);
				close(pipes[i][1]);	
			}
		}
		else
			dup2(outfile, 1);
		execute_cmd(cmd, env);
	// }
}

void	trait_redirection(t_cmds *cmds, t_envp *env, int *infile, int *outfile)
{
	t_cmds	*temp;
	// int		fds[2];
	(void)env;

	temp = cmds;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == RIGHT_REDIR)
			*outfile = open(temp->argv->argv, O_CREAT | O_TRUNC | O_RDWR, 0644);
		else if (temp->type == DOUBLE_RIGHT_REDIR)
			*outfile = open(temp->argv->argv, O_CREAT | O_APPEND | O_RDWR, 0644);
		else if (temp->type == LEFT_REDIR)
			*infile = open(temp->argv->argv, O_TRUNC | O_RDWR, 0644); // after test append the case that file doesnt exist
		// else if (temp->type == HEREDOC)
		// {
		// 	pipe(fds);
			
		// }
		temp = temp->next;
	}
	// printf("###%s###\n",temp->argv->argv);
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

void	close_fds(int **fds, int n)
{
	int	i;

	i = 0;
	while (fds[i] && i < n - 1)
	{
		close(fds[i][0]);
		close(fds[i][1]);
		i++;
	}
	i = n + 1;
	while (fds[i])
	{
		close(fds[i][0]);
		close(fds[i][1]);
		i++;
	}
}