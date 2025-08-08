/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:03:42 by osancak           #+#    #+#             */
/*   Updated: 2025/07/22 09:51:54 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read(int fd, char *buff)
{
	char	*tmp;
	int		byte;

	tmp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	byte = 1;
	while (byte > 0 && !ft_strchr(buff, '\n'))
	{
		byte = read(fd, tmp, BUFFER_SIZE);
		if (byte == 0)
			break ;
		if (byte == -1)
			return (free(tmp), free(buff), NULL);
		tmp[byte] = '\0';
		buff = gnl_strjoin(buff, tmp, 1);
	}
	free(tmp);
	return (buff);
}

static char	*ft_line(char *buff)
{
	char	*res;
	int		i;

	if (!buff || !*buff)
		return (NULL);
	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	res = ft_calloc(i + 2, sizeof(char));
	i = -1;
	while (buff[++i] && buff[i] != '\n')
		res[i] = buff[i];
	if (buff[i] && buff[i] == '\n')
		res[i++] = '\n';
	return (res);
}

static char	*ft_next(char *buff)
{
	char	*res;
	char	*tmp;
	int		i;

	tmp = buff;
	while (*buff && *buff != '\n')
		buff++;
	if (!*buff || !*(buff + 1))
		return (free(tmp), NULL);
	res = ft_calloc(ft_strlen(buff++) + 1, sizeof(char));
	i = 0;
	while (*buff)
		res[i++] = *buff++;
	free(tmp);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*line;

	if (fd == -42)
		return (free(buff), NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buff)
		buff = ft_calloc(1, sizeof(char));
	buff = ft_read(fd, buff);
	if (!buff)
		return (NULL);
	line = ft_line(buff);
	buff = ft_next(buff);
	return (line);
}
