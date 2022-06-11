/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-iaz <yait-iaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:06:59 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/06/10 15:06:48 by yait-iaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while ((str1[i] != '\0' || str2[i] != '\0') && n > 0)
	{
		if (str1[i] != str2[i])
		{
			return (str1[i] - str2[i]);
		}
		i++;
		n--;
	}
	return (0);
}

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