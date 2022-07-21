/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 18:12:36 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/21 09:22:21 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/builtins.h"
#include "../headers/minishell.h"
#include "../headers/struct.h"

void	sig_handler(int signal)
{
	if (signal == SIGINT && g_minishell.herdoc
		&& !g_minishell.child)
	{
		kill(g_minishell.herdoc, SIGKILL);
		g_minishell.herdoc = 0;
	}
	else if (signal == SIGINT && !g_minishell.herdoc
		&& !g_minishell.child)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGINT && !g_minishell.herdoc
		&& g_minishell.child)
	{
		kill(g_minishell.child, SIGKILL);
		g_minishell.child = 0;
	}
}
