/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_ad.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:43:15 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/20 15:06:45 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/struct.h"
#include "../headers/minishell.h"
#include "../headers/builtins.h"

char	*ft_strjoin_ad(char *s1, char *s2, int cond)
{
	size_t	len;
	char	*join;
	size_t	i;
	size_t	j;
	size_t	k;
	
	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		s2 = ft_strdup("");
	len = ft_strlen(s1) + ft_strlen(s2);
	join = (char *)malloc(sizeof(char) * (len + 1));
	if (!join)
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	while (s1[k])
		join[i++] = s1[k++];
	k = 0;
	while (s2[k])
		join[i++] = s2[k++];
	join[i] = '\0';
	free_str(s1, s2, cond);
	return (join);
}

void	free_str(char *str1, char *str2, int cond)
{
	if (cond == 1)
		free (str1);
	else if (cond == 2)
		free (str2);
	else if (cond == 3)
	{
		free (str1);
		free (str2);
	}
}