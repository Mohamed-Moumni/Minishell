/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:52:16 by mmoumni           #+#    #+#             */
/*   Updated: 2022/06/30 16:01:39 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/struct.h"
#include "../headers/minishell.h"
#include "../headers/builtins.h"

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	int		i;
	int		left;
	size_t	dst_l;

	i = 0;
	dst_l = ft_strlen(dst);
	left = dstsize - dst_l - 1;
	if (dstsize < dst_l)
		return (dstsize + ft_strlen(src));
	while (src[i] && left > 0)
	{
		dst[dst_l + i] = src[i];
		left--;
		i++;
	}
	dst[dst_l + i] = '\0';
	return (dst_l + ft_strlen(src));
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen((char *)src));
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
