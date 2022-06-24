/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:36:36 by mmoumni           #+#    #+#             */
/*   Updated: 2022/06/17 14:41:42 by mmoumni          ###   ########.fr       */
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

void	ft_cd(t_envp *envp, const char *str)
{
	const char *pathname;

	if (ft_strcmp(str, "") == 0)
	{
		pathname = (const char *)envp->value[1];
		chdir(pathname);
	}
	else
	{
		
	}
}

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