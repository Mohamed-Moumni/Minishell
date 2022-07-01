/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 22:24:58 by mmoumni           #+#    #+#             */
/*   Updated: 2022/06/29 22:25:12 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	checkcmp(char *num, int plus, int minus)
{
	if (minus == 1)
	{
		if (ft_strcmp(&num[minus], MIN) > 0)
			return (1);
	}
	else
	{
		if (ft_strcmp(&num[plus], MAX) > 0)
			return (1);
	}
	return (0);
}

int	is_integer(char *num)
{
	int	i;
	int	minus;
	int	plus;

	i = 0;
	minus = 0;
	plus = 0;
	while (num[i])
		i++;
	if (num[0] == '-' || num[0] == '+')
	{
		if (num[0] == '-')
			minus = 1;
		if (num[0] == '+')
			plus = 1;
		i -= 1;
	}
	if (i > 10)
		return (1);
	if (i == 10)
		return (checkcmp(num, plus, minus));
	return (0);
}

int	is_number(char *num)
{
	int	i;

	i = 0;
	if (num[i] == '-')
		return (1);
	if ((num[i] == '+') && ft_strlen(num) > 1)
		i++;
	while (num[i])
	{
		if (num[i] < '0' || num[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_number(char **num)
{
	int	i;

	i = 0;
	while (num[i])
	{
		if (is_number(num[i]))
			return (1);
		if (is_integer(num[i]))
			return (1);
		i++;
	}
	return (0);
}