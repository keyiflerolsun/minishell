/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 09:23:12 by osancak           #+#    #+#             */
/*   Updated: 2025/08/30 10:24:11 by osancak          ###   ########.fr       */
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
			return (EXIT_SUCCESS);
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

static void	heredoc_sigint_handler(int sig)
{
	t_vars	*vars;

	(void)sig;
	vars = static_vars(NULL);
	ft_printf("\n");
	close(vars->last_exit_code);
	ft_clear();
	exit(130);
}

static void	child_heredot(t_vars *vars, t_pipes *pipes, char *limiter)
{
	int		exit_code;

	signal(SIGINT, heredoc_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	vars->last_exit_code = open("here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (vars->last_exit_code < 0)
		error_exit("child_heredot » open", NULL);
	exit_code = get_input(vars->last_exit_code, limiter);
	close(vars->last_exit_code);
	close_fd(*pipes);
	ft_clear();
	exit(exit_code);
}

void	ft_heredot(t_vars *vars, t_pipes *pipes, char *limiter)
{
	pid_t			pid;
	__sighandler_t	prev_sigint;

	prev_sigint = signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		child_heredot(vars, pipes, limiter);
	if (pid < 0)
		error_exit("ft_heredot » fork", NULL);
	ft_wait_pid(vars, pid);
	signal(SIGINT, prev_sigint);
}
