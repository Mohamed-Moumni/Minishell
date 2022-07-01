/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:21:22 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/07/01 07:32:15 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/struct.h"
#include "../headers/minishell.h"
#include "../headers/builtins.h"

static int	ft_strchri(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	int		i;
	int		a;
	int		end;
	char	*str;

	i = 0;
	a = 0;
	if (!s1 || !set)
		return (0);
	end = (int)ft_strlen(s1) - 1;
	while (s1[i] && ft_strchri(set, s1[i]) == 1)
		i++;
	while (s1[end] && ft_strchri(set, s1[end]) == 1)
		end--;
	end += 1;
	if (s1[i] == '\0')
		str = ft_strdupi("", 0);
	else
		str = ft_strdupi(&s1[i], (end - i));
	free(s1);
	return (str);
}
