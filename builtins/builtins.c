/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:36:36 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/21 15:57:49 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/struct.h"
#include "../headers/minishell.h"
#include "../headers/builtins.h"

void	ft_echo(char **str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (is_nl_valid(str[i]))
			break ;
		i++;
	}
	if (i > 0 && is_nl_valid(str[i - 1]) == 0)
		ft_print(&str[i], 0);
	else
		ft_print(&str[i], 1);
	g_minishell.exit_status = 0;
	free(str);
}

void	ft_pwd(char **argv)
{
	char	cwd[PATH_MAX];
	char	*path;

	(void)argv;
	path = getcwd(cwd, PATH_MAX);
	if (!path)
		return ;
	printf("%s\n", path);
	g_minishell.exit_status = 0;
}

char	*ft_cd_home(char *path)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
	{
		printf("HOME not set!\n");
		g_minishell.exit_status = 1;
		return (0);
	}
	if (chdir(home) < 0)
	{
		free(home);
		return (0);
	}
	return (path + 1);
}

int	cd_exe(char *path, char *pwd)
{
	int	home;

	home = 0;
	if (path[0] == '~' || !path[0])
	{
		path = ft_cd_home(path);
		home = 1;
	}
	if (path[0] == '/')
	{
		if (home == 0)
			chdir("/");
		path++;
	}
	if (path[0])
	{
		if (chdir(path) < 0)
		{
			chdir(pwd);
			printf("%s no such file or directory!\n", path);
			g_minishell.exit_status = 1;
			return (0);
		}
	}
	return (1);
}

int	ft_cd(t_envp **env, t_char *argv)
{
	char	*path;
	char	*pwd;
	char	cwd[PATH_MAX];
	t_envp	*pwd_env;
	t_envp	*temp;

	if (!argv->next)
		path = ft_strdup("");
	else
		path = ft_strdup(argv->next->argv);
	pwd = getcwd(cwd, PATH_MAX);
	pwd_env = search_key(*env, "PWD");
	temp = search_key(*env, "OLDPWD");
	if (temp)
		free(temp->value);
	temp->value = pwd_env->value;
	if (cd_exe(path, pwd))
		g_minishell.exit_status = 0;
	pwd_env->value = getcwd(NULL, 10000);
	free(path);
	g_minishell.exit_status = 0;
	return (1);
}
