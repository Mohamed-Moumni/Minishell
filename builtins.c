/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-iaz <yait-iaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:36:36 by mmoumni           #+#    #+#             */
/*   Updated: 2022/06/18 21:33:41 by yait-iaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_unset(t_envp *envp, char *env_to_unset)
{
	t_envp	*ret;
	t_envp	*prev_env;
	t_envp	*next_env;

	ret = search_key(envp, env_to_unset);
	if (ret == NULL)
		return (-1);
	while (envp->next != ret)
	{
		envp = envp->next;
	}
	prev_env = envp;
	next_env = envp->next->next;
	prev_env->next = next_env;
	free(ret);
	return (1);
}

int	ft_cd(char *path)
{
	int		i;
	char	**new_path;

	i = 0;
	new_path = ft_split(path, '/');
	while (new_path[i])
	{
		if (chdir(new_path[i]) < 0)
		{
			printf("no such file or directory: %s\n", path);
			break ;
		}
		i++;
	}
	free (path);
	return (1);
}

int	main()
{
	char *str;

	str = readline(">>");
	while (str)
	{
		ft_cd(str);
		str = readline(">>");
	}
}

// int main(int ac, char **av, char **env)
// {
// 	t_envp	*envp;
// 	t_envp	*tmp;
	
// 	envp = envp_to_list(env);
// 	// ft_pwd(envp);
// 	// tmp = envp;
// 	// while (envp)
// 	// {
// 	// 	printf("%s=",envp->key);
// 	// 	printf("%s\n",envp->value);
// 	// 	envp = envp->next;
// 	// }
// 	t_envp *ret;

// 	// ret = search_key(envp, av[1]);
// 	ft_unset(envp, av[1]);
// 	tmp = envp;
// 	while (envp)
// 	{
// 		printf("%s=",envp->key);
// 		printf("%s\n",envp->value);
// 		envp = envp->next;
// 	}
// }