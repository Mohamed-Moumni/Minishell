/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:36:36 by mmoumni           #+#    #+#             */
/*   Updated: 2022/06/15 17:50:43 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_nl_valid(char *str);
void	ft_print(char **str, int condition);

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
		printf("%s", str[i]);
	else
		printf("%s\n", str[i]);
}