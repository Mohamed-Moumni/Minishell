/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_last.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 19:02:41 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/20 09:28:43 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/struct.h"
#include "../headers/minishell.h"
#include "../headers/builtins.h"

t_envp	*ft_list_last(t_envp *env_list)
{
	t_envp	*temp_envp;

	temp_envp = env_list;
	while (temp_envp->next != NULL)
		temp_envp = temp_envp->next;
	return (temp_envp);
}
