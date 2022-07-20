/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:26:52 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/07/20 13:49:09 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/struct.h"
#include "../headers/minishell.h"
#include "../headers/builtins.h"

int	ft_char_counter(char *str, char ch)
{
	int n;
	int	i;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] == ch)
			n++;
		i++;
	}
	return (n);
}
