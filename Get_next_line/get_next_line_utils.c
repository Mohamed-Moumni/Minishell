/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 20:13:34 by mmoumni           #+#    #+#             */
/*   Updated: 2022/06/30 13:44:03 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/struct.h"
#include "../headers/minishell.h"

char	*ft_strdup(char *s1)
{
	size_t	i;
	size_t	len;
	char	*str;

	len = ft_strlen(s1);
	i = 0;
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

