/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 18:12:36 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/18 19:43:35 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/builtins.h"
#include "../headers/minishell.h"
#include "../headers/struct.h"

void	sig_handler(int signal)
{
	if (signal == SIGINT && g_minishell.herdoc) 
	{
		kill(g_minishell.herdoc, SIGKILL);
		g_minishell.herdoc = 0;
		// printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		// rl_redisplay();
	}
	else if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}