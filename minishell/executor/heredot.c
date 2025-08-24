/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 09:23:12 by osancak           #+#    #+#             */
/*   Updated: 2025/08/24 13:01:34 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "executor.h"

static void	get_input(int fd, char *limiter)
{
	char	*line;

	line = "";
	while (line)
	{
		line = readline(BOLD_YELLOW "heredot" BOLD_RED " > " RESET);
		if (!ft_strcmp(line, limiter))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

static t_vars	*g_vars;

static void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	ft_printf("\n");
	ft_clear(g_vars);
	exit(130);
}

static void	child_heredot(t_vars *vars, char *limiter)
{
	int	fd;

	signal(SIGINT, heredoc_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	fd = open("here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		error_exit("here_doc", 1);
	get_input(fd, limiter);
	close(fd);
	ft_clear(vars);
	exit(EXIT_SUCCESS);
}

void	ft_heredot(t_vars *vars, char *limiter)
{
	pid_t	pid;
	void	(*prev_sigint)(int);

	g_vars = vars;
	prev_sigint = signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		child_heredot(vars, limiter);
	if (pid < 0)
		error_exit("heredot", 1);
	ft_wait_pid(vars, pid, prev_sigint);
}
