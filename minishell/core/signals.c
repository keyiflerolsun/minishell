/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:12:48 by osancak           #+#    #+#             */
/*   Updated: 2025/08/31 12:45:46 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static void	sigint_handler(int signum)
{
	t_vars	*vars;

	(void)signum;
	vars = static_vars(NULL);
	if (vars->tmp == -42)
		return ;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	vars->last_exit_code = 130;
	rl_redisplay();
}

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
