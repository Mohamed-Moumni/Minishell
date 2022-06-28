/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 10:31:42 by mmoumni           #+#    #+#             */
/*   Updated: 2022/06/28 09:42:40 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/builtins.h"

char    *cmd_valid(char *cmd)
{
	char	**paths;
	int		i;
	char	*temp;

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
	return (0);
}