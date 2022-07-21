/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:41:53 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/20 11:58:49 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/builtins.h"
#include "../headers/struct.h"

void	exit_with_args(t_char *args)
{
	t_char	*temp;

	temp = args;
	if (check_number(temp->argv))
	{
		printf("exit\nmininshell: exit: %s: numeric argument required\n", \
		temp->argv);
		g_minishell.exit_status = 255;
		exit (g_minishell.exit_status);
	}
	else if (check_number(temp->argv) || temp->next)
	{
		printf ("exit\nminishell: exit: too many arguments\n");
		g_minishell.exit_status = 1;
	}
	else
	{
		g_minishell.exit_status = ft_atoi(args->next->argv);
		exit (g_minishell.exit_status);
	}
}

void	ft_exit(t_char *args)
{
	t_char			*temp;

	temp = args->next;
	if (temp == NULL)
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	else
		exit_with_args(temp);
}
