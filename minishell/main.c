/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:24:09 by osancak           #+#    #+#             */
/*   Updated: 2025/08/08 16:50:19 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	sigint_handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	vars;
	char	*line;

	(void)argc;
	(void)argv;
	set_path(&vars, envp);
	if (!vars.path)
		error_exit("PATH environment variable not found or invalid", 0);
	setup_signals();
	while (1)
	{
		line = readline(MAGENTA "minismet" BLUE " ¢ " RESET);
		if (!line)
			break ;
		if (*line)
			add_history(line);
		waitpid(ft_cmd(vars, line, envp), NULL, 0);
		free(line);
	}
	rl_clear_history();
	printf("\n\n" RED "exit" RESET "\n\n");
	return (EXIT_SUCCESS);
}
