/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:09:42 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/06/30 13:45:24 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/struct.h"
#include "../headers/minishell.h"
#include "../headers/builtins.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	advanced_strlen(char *start, char *end)
{
	int	i;

	i = 0;
	while (start[i] && &start[i] != &end[0])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while ((str1[i] != '\0' || str2[i] != '\0'))
	{
		if (str1[i] != str2[i])
		{
			return (str1[i] - str2[i]);
		}
		i++;
	}
	return (0);
}

char	*ft_substr(char *s, int start, int len)
{
	int		i;
	char	*str;

	i = 0;
	if (!s)
		return (0);
	if (len > ft_strlen(&s[start]))
		len = ft_strlen(&s[start]);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	if (start >= ft_strlen(s))
	{
		if (start == ft_strlen(s) && len != 0)
			str[i++] = s[start];
		str[i] = '\0';
		return (str);
	}
	while (s[start] && len > i)
	{
		str[i] = s[start++];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strchr(char *s, int c)
{
	int		i;
	char	ch;

	i = 0;
	ch = ((char) c);
	while (s[i] != '\0')
	{
		if (s[i] == ch)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == ch)
		return ((char *)&s[i]);
	return (&s[i]);
}
