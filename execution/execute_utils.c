/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 10:31:42 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/13 18:41:51 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/struct.h"
#include "../headers/minishell.h"
#include "../headers/builtins.h"

char    *cmd_valid(char *cmd)
{
	char	**paths;
	int		i;
	char	*temp;

	if (check_absolut_path(cmd))
	{
		if (!access(cmd, (X_OK & F_OK)))
			return (cmd);
		printf("minishell: %s: No such file or directory", cmd);
		return (NULL);
	}
	i = 0;
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
	printf("minishell: %s: command not found", cmd);
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
	if (cmd[0] == '/' || (ft_strlen(cmd) >= 2 && (cmd[0] == '.' && cmd[1] == '/'))||
		((cmd[0] == '.' || cmd[1] == '.' || cmd[2] == '/') && ft_strlen(cmd) >= 3))
		return (1);
	return (0);
}
