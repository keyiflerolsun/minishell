/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 09:23:12 by osancak           #+#    #+#             */
/*   Updated: 2025/07/23 17:54:14 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	get_input(int fd, char *limiter)
{
	char	*line;

	line = "";
	while (line)
	{
		ft_printf("%s%sheredot %s%s>%s ", MAGENTA, BOLD, BLUE, BOLD, RESET);
		line = get_next_line(0);
		if (ft_strstr(line, limiter))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
}

pid_t	ft_heredot(char *limiter)
{
	pid_t	pid;
	int		fd;

	pid = fork();
	if (pid == 0)
	{
		fd = open("here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			error_exit("here_doc", 1);
		get_input(fd, limiter);
		close(fd);
		exit(EXIT_SUCCESS);
	}
	if (pid < 0)
		error_exit("heredot", 1);
	return (pid);
}
