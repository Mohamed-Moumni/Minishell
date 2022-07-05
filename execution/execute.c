/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 10:07:54 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/05 16:15:53 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/struct.h"
#include "../headers/minishell.h"
#include "../headers/builtins.h"

int	node_init_cmd(t_cmds **list, e_token token)
{
	*list = malloc(sizeof(t_cmds));
	if (!(*list))
		return (0);
	(*list)->next = NULL;
	(*list)->prev = NULL;
	(*list)->argv = NULL;
	(*list)->type = token;
	return (1);
}

int	add_node_cmd(t_cmds **cmds, e_token token)
{
	t_cmds	*tmp;
	t_cmds	*new_node;

	if (!(*cmds))
	{
		if (!node_init_cmd(cmds, token))
			return (0);
	}
	else
	{	
		tmp = *cmds;
		if (!node_init_cmd(&new_node, token))
			return (0);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
		new_node->prev = tmp;
	}
	return (1);
}

int	node_char_init(t_char **arg, char *word)
{
	*arg = malloc(sizeof(t_char));
	if (!(*arg))
		return (0);
	(*arg)->argv = word;
	(*arg)->next = NULL;
	return (1);
}

int	add_char_node(t_char **arg, char *word)
{
	t_char	*tmp;
	t_char	*new_node;

	if (!(*arg))
	{
		if (!node_char_init(arg, word))
			return (0);
	}
	else
	{	
		tmp = *arg;
		if (!node_char_init(&new_node, word))
			return (0);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
	return (1);
}

void	print_char(t_char *ch)
{
	t_char *tmp;

	tmp = ch;
	while (tmp)
	{
		printf("arg: \n%s\n", tmp->argv);
		tmp = tmp->next;
	}
}

int	element_count(t_char *list)
{
	int	n;
	t_char	*tmp;

	n = 0;
	tmp = list;
	while (tmp)
	{
		n++;
		tmp = tmp->next;
	}
	return (n);
}

t_cmds	*cmd_last_node(t_cmds *cmd)
{
	t_cmds	*tmp;

	tmp = cmd;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

int	treat_word(t_cmds **cmds, t_lexer *node, t_envp *env, e_token token)
{
	char	*start;
	char	*end;
	char	*word;

	if (!add_node_cmd(cmds, token))
		return (0);
	if (node->prev && node->prev->token == HEREDOC && node->token != SINGLE_QUOTE)
	{
		ft_expand(&(node->content), env, node);
		return (add_char_node(&cmd_last_node(*cmds)->argv, ft_strdupi(node->content, ft_strlen(node->content))));
	}
	node->content = ft_strtrim(node->content, " ");
	start = node->content;
	end = start;
	while (start[0] && end[0])
	{
		end++;
		if ((end[0] == ' ' && between_quote(start, end, '"') \
			&& between_quote(start, end, '\'')) || !end[0])
		{
			printf("start: |%s| -> |%s|\n", start, end);
			if (start[0] != ' ')
			{	
				word = hundle_quote(ft_substr(start, 0, \
					advanced_strlen(start, end)), env, node);
				if (!word)
					return (0);
				if (!add_char_node(&cmd_last_node(*cmds)->argv, word))
					return (0);
			}
			start = end + 1;
		}
	}
	return (1);
}

t_char	*char_last_node(t_char *node)
{
	t_char *ch;

	ch = node;
	while (ch->next)
		ch = ch->next;
	return (ch);
}

int	adjust_filename(t_cmds *cmd)
{
	t_char	*tmp;
	t_cmds	*prev_cmd;

	tmp = cmd->argv->next;
	cmd->argv->next = NULL;
	prev_cmd = cmd->prev;
	printf("type: %d\n", prev_cmd->type);
	while (prev_cmd->type != WORD && prev_cmd->next)
	{
		prev_cmd = prev_cmd->prev;
		printf("type: %d\n", prev_cmd->type);
	}
	char_last_node(prev_cmd->argv)->next = tmp;
	return (1);
}

int	treat_redir(t_cmds **cmds, t_envp *env, t_lexer *node)
{
	t_cmds	*tmp;

	if (!treat_word(cmds, node->next, env, node->token))
		return (0);
	tmp = *cmds;
	while (tmp->next)
		tmp = tmp->next;
	if (element_count(tmp->argv) > 1 && node->token != PIPE)
		adjust_filename(cmd_last_node(*cmds));
	return (1);
}

void	print_cmd(t_cmds *cmd)
{
	while (cmd)
	{
		printf("----------------------------\n");
		print_char(cmd->argv);
		printf("token: %d\n", cmd->type);
		printf("-----------------------\n");
		cmd = cmd->next;
	}
}

int start_execution(t_lexer *list, t_envp *env)
{
	t_cmds	*cmds;
	t_lexer	*tmp;
	t_exec  *exec;

	tmp = list;
	cmds = NULL;
	while (tmp)
	{
		if (tmp->token == WORD)
		{
			if (!treat_word(&cmds, tmp, env, WORD))
				return (0);
		}
		else
		{
			if (!treat_redir(&cmds, env, tmp))
				return (0);
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	exec = cmds_to_exec(cmds);
	print_exec(exec);
	// print_cmd(cmds);
	return (1);
}

// int	open_files(t_cmds *cmds)
// {
// 	t_cmds	*temp;

// 	temp = cmds;
// 	while (temp)
// 	{
// 		if (temp->type == RIGHT_REDIR)
// 		{
			
// 		}
// 	}
// }
// int	**open_pipes(int n)
// {
// 	int i;
// 	int	*fds[2];

// }

int	**two_dim_arr(int a)
{
	int i;
	int	**tab;

	tab = (int **)malloc(sizeof(int *) * a);
	i = 0;
	while (i < a)
	{
		tab[i] = (int *)malloc(sizeof(int) * 2);
		i++;
	}
	return (tab);
}
// void	run_execution(t_cmds *cmds, t_envp *env)
// {
// 	t_cmds	*tmp_cmd;
// 	int		pipes;
// 	char	**av;
// 	int		pid;
// 	int		**fds;
// 	int		i;

// 	tmp_cmd = cmds;
// 	pipes = how_many_pipes(cmds);
// 	i = 0;
// 	if (pipes == 0)
// 	{
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			av = conv_t_char_to_tab(cmds->argv);
// 			execve(av[0], av, list_to_envp(env));
// 		}
// 	}
// 	else
// 	{
// 		fds = two_dim_arr(pipes);
// 		while (i < pipes)
// 		{
// 			pipe(fds[i]);
// 			i++;
// 		}
// 		while (tmp_cmd)
// 		{
// 			if (tmp_cmd->prev == NULL)
// 			{
// 				close()
// 			}
// 		}
// 	}
// }

// void	run_command(t_cmds *cmds, t_envp *env, int *read_pipe, int *write_pipe)
// {
// 	char	**argv;
// 	char	**envp;
// 	int		pid;
// 	int		status;

// 	argv = conv_t_char_to_tab(cmds->argv);
// 	envp = list_to_envp(env);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		if (read_pipe == NULL && write_pipe == NULL)
// 		{
// 			argv[0] = cmd_valid(argv[0]);
// 			if (argv[0] == NULL)
// 				perror("command not found");
// 			execve (cmd_valid(argv[0]), argv, envp);
// 		}
// 		else if(read_pipe == NULL)
// 		{
// 			close(write_pipe[0]);
// 			dup2(write_pipe[1], 1);
// 			close(write_pipe[1]);
// 			if (argv[0] == NULL)
// 				perror("command not found");
// 			execve(cmd_valid(argv[0]), argv, envp);	
// 		}
// 		else if (write_pipe == NULL)
// 		{
// 			close(read_pipe[1])
// 		}
// 	}
// 	waitpid(pid, &status, 0);
// }
// void	run_pipe(t_cmds *cmds)
// {
// 	char	**tab;
// 	char	**env;
// 	int		pid;
	
// 	if (pipe(cmds->fd) == -1)
// 		return ;
// 	if (cmds->prev == NULL)
// 	{
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 				close (cmds->fd[0]);
// 				dup2 (cmds->fd[1], 1);
// 				close (cmds->fd[1]);
// 				expande(cmds->argv);
// 				tab = t_char_to_argv();
// 				env = env_list_to_tab();
// 				execve(tab[0], tab, env);
// 		}
// 	}
// 	else
// 	{
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			close(cmds->prev->fd[1]);
// 			dupe2(cmds->prev->fd[0], 0);
// 			close(cmds->prev->fd[0]);
// 			close(cmds->fd[0]);
// 			dupe2(cmds->fd[1], 1);
// 			close(cmds->fd[1]);
// 			expande(cmds->argv);
// 			tab = t_char_to_argv();
// 			env = env_list_to_tab();
// 			execve(tab[0], tab, env);
// 		}
// 	}
// 	waitpid(pid, NULL, 0);
// }

// void	run_redirection(t_cmds *cmds)
// {
// 	char	**tab;
// 	char	**env;
// 	int		pid;
// 	char	*buff;
// 	int		fd_file;

// 	if (cmds->prev == NULL)
// 	{
// 		expande(cmds->argv);
// 		tab = t_char_to_argv();
// 		env = env_list_to_tab();
// 		if (cmds->type == RIGHT_REDIR)
// 		{
// 			fd_file = open(tab[0], (O_CREAT |  O_WRONLY | O_TRUNC), 0644);
// 			if (fd_file == -1)
// 				return ;
// 			if (read (STDIN_FILENO, buff, 0) == -1)
// 				return ;
// 			if (write(fd_file, buff, 0) == -1)
// 				return ;
// 		}
// 		else if (cmds->type == DOUBLE_RIGHT_REDIR)
// 		{
// 			fd_file = open(tab[0], (O_CREAT &  O_WRONLY & O_APPEND), 0644);
// 			if (fd_file == -1)
// 				return ;
// 			if (read (STDIN_FILENO, buff, 0) == -1)
// 				return ;
// 			if (write(fd_file, buff, 0) == -1)
// 				return ;
// 		}
// 	}
// 	else
// 	{
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			if (cmds->type == RIGHT_REDIR)
// 			{
// 				fd_file = open(tab[0], (O_CREAT &  O_WRONLY & O_TRUNC), 0644);
// 				if (fd_file == -1)
// 					return ;		
// 				close (cmds->prev->fd[1]);
// 				if (read(cmds->prev->fd[0], buff, 0) == -1)
// 					return ;
// 				if (write(fd_file, buff, 0) == -1)
// 					return ;
// 			}
// 			else if (cmds->type == DOUBLE_RIGHT_REDIR)
// 			{
// 				fd_file = open(tab[0], (O_CREAT &  O_WRONLY & O_APPEND), 0644);
// 				if (fd_file == -1)
// 					return ;
// 				close (cmds->prev->fd[1]);
// 				if (read (cmds->prev->fd[0], buff, 0) == -1)
// 					return ;
// 				if (write(fd_file, buff, 0) == -1)
// 					return ;
// 			}
// 		}
// 		waitpid (pid, NULL, 0);
// 	}
// }


