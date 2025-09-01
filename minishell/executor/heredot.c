/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 09:23:12 by osancak           #+#    #+#             */
/*   Updated: 2025/08/31 17:35:06 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "core.h"
#include "executor.h"

static int	process_line(int *fd, char *line, char **limiters, int *curr)
{
	if (!ft_strcmp(line, limiters[*curr]))
	{
		free(line);
		return (1);
	}
	write(*fd, line, ft_strlen(line));
	write(*fd, "\n", 1);
	free(line);
	return (0);
}

static int	get_input(int *fd, char **limiters)
{
	char	*line;
	int		curr;

	curr = 0;
	while (limiters[curr])
	{
		line = readline(BOLD_YELLOW "heredot" BOLD_RED " > " RESET);
		if (!line)
		{
			write_err("minismet", "heredoc delimited by end-of-file\n");
			curr++;
			continue ;
		}
		if (process_line(fd, line, limiters, &curr))
		{
			if (limiters[++curr])
			{
				close(*fd);
				*fd = open("here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
				if (*fd < 0)
					return (EXIT_FAILURE);
			}
		}
	}
	return (EXIT_SUCCESS);
}

static void	heredoc_sigint_handler(int sig)
{
	t_vars	*vars;

	(void)sig;
	vars = static_vars(NULL);
	ft_printf("\n");
	close(vars->tmp);
	ft_clear();
	exit(130);
}

static void	child_heredot(t_vars *vars, t_pipes *pipes, char **limiters)
{
	int	exit_code;

	signal(SIGINT, heredoc_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	vars->tmp = open("here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (vars->tmp < 0)
		error_exit("child_heredot » open", NULL);
	exit_code = get_input(&vars->tmp, limiters);
	close(vars->tmp);
	close_fd(pipes);
	ft_clear();
	exit(exit_code);
}

void	ft_heredot(t_vars *vars, t_pipes *pipes, char **limiters)
{
	pid_t			pid;
	__sighandler_t	prev_sigint;

	prev_sigint = signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		child_heredot(vars, pipes, limiters);
	if (pid < 0)
		error_exit("ft_heredot » fork", NULL);
	ft_wait_pid(vars, pid);
	signal(SIGINT, prev_sigint);
}
