/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 18:12:36 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/20 23:01:45 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/builtins.h"
#include "../headers/minishell.h"
#include "../headers/struct.h"

void	sig_handler(int signal)
{
	if (signal == SIGINT && !g_minishell.herdoc
		&& g_minishell.child)
		;
	else if (signal == SIGINT && g_minishell.herdoc)
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
}
