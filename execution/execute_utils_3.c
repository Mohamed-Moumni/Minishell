/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:40:38 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/20 09:41:19 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/struct.h"
#include "../headers/minishell.h"
#include "../headers/builtins.h"

int	**two_dim_arr(int a)
{
	int	i;
	int	**tab;

	tab = (int **)malloc(sizeof(int *) * (a + 1));
	i = 0;
	while (i < a)
	{
		tab[i] = (int *)malloc(sizeof(int) * 2);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}