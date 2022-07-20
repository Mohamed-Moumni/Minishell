/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 10:31:42 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/20 11:01:17 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/struct.h"
#include "../headers/minishell.h"
#include "../headers/builtins.h"

char	*cmd_valid(char *cmd)
{
	char	**paths;
	int		i;
	char	*temp;
	int		cond;
	char	*path;

	i = 0;
	cond = 0;
	path = check_path(cmd, &cond);
	if (!cond)
		return (path);
	paths = std_paths(_PATH_STDPATH);
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], cmd);
		if (!access(temp, (X_OK & F_OK)))
			return (temp);
		free (temp);
		i++;
	}
	free (paths);
	printf("minishell: %s: command not found\n", cmd);
	g_minishell.exit_status = 127;
	return (NULL);
}

char	*check_path(char *path, int *cond)
{
	if (g_minishell.unset_path == 1)
	{
		printf("minishell: %s: No such file or directory\n", path);
		g_minishell.exit_status = 1;
		return (NULL);
	}
	if (check_absolut_path(path))
	{
		if (access(path, (F_OK)))
		{
			printf("minishell: %s: No such file or directory\n", path);
			g_minishell.exit_status = 1;
			return (NULL);
		}
		else if (access(path, (X_OK)))
		{
			printf("minishell: %s: Permission denied\n", path);
			g_minishell.exit_status = 126;
			return (NULL);
		}
		return (path);
	}
	*cond = 1;
	return (NULL);
}

char	**std_paths(char *str)
{
	int		i;
	char	**paths;
	char	*temp;

	i = 0;
	paths = ft_split(str, ':');
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		free (paths[i]);
		paths[i] = temp;
		i++;
	}
	return (paths);
}

int	check_absolut_path(char *cmd)
{
	if (cmd[0] == '/')
		return (1);
	if ((ft_strlen(cmd) >= 2 && (cmd[0] == '.' && cmd[1] == '/')))
		return (1);
	if ((ft_strlen(cmd) >= 3 && (cmd[0] == '.' || cmd[1] == '.' || \
		cmd[2] == '/')))
		return (1);
	return (0);
}
