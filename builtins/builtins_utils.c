/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:53:42 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/16 10:38:57 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/struct.h"
#include "../headers/minishell.h"
#include "../headers/builtins.h"

int	is_nl_valid(char *str)
{
	int i;

	i = 1;
	if (str[0] == '-')
	{
		while (str[i] == 'n')
			i++;
		if (str[i] != '\0')
			return (1);
		return (0);
	}
	return (1);
}

void	ft_print(char **str, int condition)
{
	int i;

	i = 0;
	while (str[i] && str[i + 1] != NULL)
	{
		printf("%s ", str[i]);
		i++;		
	}
	if (condition == 0)
	{
		if (!str[i])
			printf("");
		else
			printf("%s", str[i]);
	}
	else
	{
		if (!str[i])
			printf("");
		else
			printf("%s\n", str[i]);
	}
}
