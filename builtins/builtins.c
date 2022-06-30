/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:36:36 by mmoumni           #+#    #+#             */
/*   Updated: 2022/06/30 13:43:40 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/struct.h"
#include "../headers/minishell.h"
#include "../headers/builtins.h"

void	echo(char ** str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (is_nl_valid(str[i]))
			break ;
		i++;
	}
	if (is_nl_valid(str[i - 1]) == 0)
		ft_print(&str[i], 1);
	else
		ft_print(&str[i], 0);
}


void	ft_pwd(t_envp *envp_list)
{
	t_envp	*pwd;

	pwd = search_key(envp_list,"PWD");
	printf("%s\n", pwd->value);
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

int	ft_cd(t_envp *env, char *path)
{
	int		home;
	char	*pwd;
	t_envp	*pwd_env;

	home = 0;
	pwd = getcwd(NULL, 1000);
	pwd_env = search_key(env, "PWD");
	search_key(env, "OLDPWD")->value = pwd_env->value;
	if (path[0] == '~' || !path[0])
	{
		path = ft_cd_home( path);
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

int		ft_unset(t_envp *env, char *key)
{
	t_envp	*tmp1;
	t_envp	*tmp2;

	tmp1 = env;
	tmp2 = search_key(env, key);
	if (!key[0] || !tmp2)
		return (1);
	while (tmp1->next != tmp2)
		tmp1 = tmp1->next;
	tmp1->next = tmp2->next;
	free(tmp2);
	return (1);
}
// void	ft_cd(t_envp *envp, const char *str)
// {
// 	const char *pathname;

// 	if (ft_strcmp((char *)str, "") == 0)
// 	{
// 		pathname = (const char *)envp->value[1];
// 		chdir(pathname);
// 	}
// 	else
// 	{
		
// 	}
// }

// int main(int ac, char **av, char **env)
// {
// 	t_envp	*envp;
// 	// char 	*dic;
// 	// t_envp	*tmp;
	
// 	envp = envp_to_list(env);
// 	// // ft_pwd(envp);
// 	// // tmp = envp;
// 	// // while (envp)
// 	// // {
// 	// // 	printf("%s=",envp->key);
// 	// // 	printf("%s\n",envp->value);
// 	// // 	envp = envp->next;
// 	// // }
// 	// t_envp *ret;

// 	// // ret = search_key(envp, av[1]);
// 	// ft_unset(envp, av[1]);
// 	// tmp = envp;
// 	// while (envp)
// 	// {
// 	// 	printf("%s=",envp->key);
// 	// 	printf("%s\n",envp->value);
// 	// 	envp = envp->next;
// 	// }
// 	char *read_line;
	
// 	while ((read_line = readline("minishell>>")))
// 	{
// 		printf("%s\n", read_line);
// 		ft_cd(envp, read_line);
// 		ft_pwd(envp);
// 	}
// }