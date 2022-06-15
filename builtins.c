/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:36:36 by mmoumni           #+#    #+#             */
/*   Updated: 2022/06/15 17:53:39 by mmoumni          ###   ########.fr       */
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
