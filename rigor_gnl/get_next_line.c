/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:58:59 by mmoumni           #+#    #+#             */
/*   Updated: 2022/07/18 19:36:52 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/builtins.h"
#include "../headers/struct.h"

static char	*read_line(char *static_buff, int fd)
{
	char	*buffer;
	int		n;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	n = 1;
	while (n > 0 && ft_strchr_gn(static_buff, '\n') == NULL)
	{	
		n = read(fd, buffer, BUFFER_SIZE);
		if (n == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[n] = '\0';
		if (n == 0)
			break ;
		static_buff = ft_strjoin_gn(static_buff, buffer);
	}
	free(buffer);
	return (static_buff);
}

static char	*backup_func(char *backup)
{
	char	*dest;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (backup[len] != '\n' && backup[len] != '\0')
		len++;
	if (backup[len] == '\0')
	{
		free(backup);
		return (NULL);
	}
	dest = ft_strdup(backup + len + 1);
	free(backup);
	if (dest[0] == '\0')
	{
		free(dest);
		return (NULL);
	}
	return (dest);
}

char	*get_next_line(int fd)
{
	static char		*backup;
	char			*line;
	int				i;
	int				len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	backup = read_line(backup, fd);
	if (backup == NULL)
		return (NULL);
	i = -1;
	len = 0;
	while (backup[len] != '\n' && backup[len] != '\0')
		len++;
	line = malloc(sizeof(char) *(len + 1));
	if (!line)
		return (NULL);
	while (++i < len)
		line[i] = backup[i];
	line[i] = '\0';
	backup = backup_func(backup);
	return (line);
}
