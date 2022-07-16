/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:36:36 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/16 18:59:22 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/struct.h"
#include "../headers/minishell.h"
#include "../headers/builtins.h"

void	ft_echo(char ** str)
{
	int	i;
	
	i = 0;
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
}

char	*ft_cd_home(char *path)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
	{
		printf("HOME not set!\n");
		return (0);
	}
	if (chdir(home) < 0)
		return (0);
	return (path + 1);
}

int	ft_cd(t_envp **env, char *path) // use t_char instead of char
{
	int		home;
	char	*pwd;
	char	cwd[PATH_MAX];
	t_envp	*pwd_env;

	home = 0;
	pwd = getcwd(cwd, PATH_MAX);
	pwd_env = search_key(*env, "PWD");
	search_key(*env, "OLDPWD")->value = pwd_env->value;
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
			return (0);
		}
	}
	pwd_env->value = getcwd(NULL, 10000);
	return (1);
}

t_envp *without_env(void)
{
	t_envp *env;
	char	cwd[PATH_MAX];
	char	*pwd;

	env = NULL;
	pwd = NULL;
	pwd = ft_strjoin("", "PWD=");
	pwd = ft_strjoin(pwd, getcwd(cwd, PATH_MAX));
	envp_add_back(&env, creat_node(pwd));
	envp_add_back(&env, creat_node(SHLVL));
	envp_add_back(&env, creat_node(USRBINENV));
	return (env);
}
