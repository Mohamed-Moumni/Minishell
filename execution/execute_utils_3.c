/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:40:38 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/20 15:07:59 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/struct.h"
#include "../headers/minishell.h"
#include "../headers/builtins.h"

int	**two_dim_arr(int a)
{
	int	i;
	int	**tab;

	tab = (int **)malloc(sizeof(int *) * (a + 1));
	i = 0;
	while (i < a)
	{
		tab[i] = (int *)malloc(sizeof(int) * 2);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

void	run_builtin(t_cmds *cmd, t_envp **env)
{
	char	*temp;
	char	**str;

	temp = cmd->argv->argv;
	if (!ft_strcmp(temp, "PWD") || !ft_strcmp(temp, "pwd"))
	{
		str = conv_t_char_to_tab(cmd->argv);
		ft_pwd(str);
		free_tab((void *)str);
	}
	else if (!ft_strcmp(temp, "ECHO") || !ft_strcmp(temp, "echo"))
	{
		str = conv_t_char_to_tab(cmd->argv);
		ft_echo(&str[1]);
		free_tab((void *)str);
	}
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

void	get_exit_status(int status)
{
	if (WIFEXITED(status))
		g_minishell.exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		g_minishell.exit_status = WTERMSIG(status) + 128;
	if (g_minishell.exit_status == 131)
		write(1, "Quit: 3\n", 9);
}

void	exceve_cmd(t_cmds *cmd, t_envp **env)
{
	char	**args;
	char	**envp;
	char	*command;

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
