/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-iaz <yait-iaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:06:59 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/06/09 13:07:11 by yait-iaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdupi(const char *s1, int l)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (l + 1));
	if (!str)
		return (0);
	while (s1[i] && l > i)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	int		l2;
	char	*str;

	i = -1;
	j = 0;
	if (!s1 || !s2)
		return (0);
	l2 = ft_strlen(s2);
	str = malloc((sizeof(char) * ft_strlen(s1)) + (sizeof(char) * l2 + 1));
	if (!str)
		return (0);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	free((void *)s1);
	return (str);
}