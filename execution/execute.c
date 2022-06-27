/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-iaz <yait-iaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 10:07:54 by mmoumni           #+#    #+#             */
/*   Updated: 2022/06/27 14:34:18 by yait-iaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	treat_word(t_cmds *cmds, t_lexer *node)
{
}

int start_execution(t_lexer *list)
{
	t_cmds	*cmds;
	t_lexer	*tmp;

	tmp = list;
	cmds = NULL;
	while (tmp)
	{
		if (tmp->token == 0)
			treat_word(cmds, tmp);
		tmp = tmp->next;
	}
}

void	run_pipe(t_cmds *cmds)
{
	
}

void	run_redirection(t_cmds *cmds)
{
	
}

