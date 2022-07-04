/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 13:17:59 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/03 13:18:38 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/builtins.h"
#include "../headers/minishell.h"
#include "../headers/struct.h"

static int	ft_digits(int n)
{
	int	digits;

	digits = 0;
	if (n <= 0)
		digits++;
	while (n != 0)
	{
		digits++;
		n = n / 10;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	long	nb;
	char	*number;
	int		nb_len;
	int		check;

	nb = n;
	nb_len = ft_digits(nb);
	number = (char *)malloc(nb_len + 1);
	if (!number)
		return (NULL);
	check = 0;
	if (nb < 0)
	{
		number[0] = '-';
		check = 1;
		nb = -nb;
	}
	number[nb_len] = '\0';
	while (--nb_len >= check)
	{
		number[nb_len] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (number);
}
