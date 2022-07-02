/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:45:27 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/02 18:48:27 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/builtins.h"
#include "../headers/minishell.h"
#include "../headers/struct.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;
	int	save;
	int	k;

	i = 0;
	if (to_find[0] == '\0')
		return (str);
	while (str[i] != '\0')
	{
		j = 0;
		save = i;
		k = i;
		while (str[k] == to_find[j] && to_find[j] != '\0' && str[k] != '\0')
		{
			k++;
			j++;
		}
		if (to_find[j] == '\0')
            return (str + save);
		i++;
	}
	return (0);
}