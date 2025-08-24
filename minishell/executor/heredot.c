/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 09:23:12 by osancak           #+#    #+#             */
/*   Updated: 2025/08/24 13:30:45 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "core.h"
#include "executor.h"

static int	get_input(int fd, char *limiter)
{
	char	*line;

	line = "";
	while (line)
	{
		line = readline(BOLD_YELLOW "heredot" BOLD_RED " > " RESET);
		if (line == NULL)
		{
			write_err("minismet", "heredoc delimited by end-of-file\n");
			return (130);
		}
		if (!ft_strcmp(line, limiter))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (EXIT_SUCCESS);
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
	int	exit_code;

	signal(SIGINT, heredoc_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	fd = open("here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		error_exit("here_doc", 1);
	exit_code = get_input(fd, limiter);
	close(fd);
	ft_clear(vars);
	exit(exit_code);
}

void	ft_heredot(t_vars *vars, char *limiter)
{
	pid_t			pid;
	__sighandler_t	prev_sigint;

	g_vars = vars;
	prev_sigint = signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		child_heredot(vars, limiter);
	if (pid < 0)
		error_exit("heredot", 1);
	ft_wait_pid(vars, pid);
	signal(SIGINT, prev_sigint);
}
