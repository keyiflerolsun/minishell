/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 18:32:25 by osancak           #+#    #+#             */
/*   Updated: 2025/08/08 17:25:28 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;36m"
# define RED "\033[0;31m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define BOLD "\033[1m"
# define RESET "\033[0m"
#include <readline/history.h>
#include <readline/readline.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

static void	sigint_handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();       		  // readline ile yeni satıra geç
	rl_replace_line("", 0); 		  // readline buffer’ını temizle
	rl_redisplay();         		  // prompt'u yeniden göster
}

static void	setup_signals(void)
{
	struct sigaction	sa;

    sa.sa_handler = sigint_handler;  // CTRL+C (SIGINT) geldiğinde sigint_handler fonksiyonu çağrılır
    sa.sa_flags = SA_RESTART;        // Sistem çağrıları kesilmez, (örneğin readline) devam eder
	sigemptyset(&sa.sa_mask);        // sa_mask (handler çalışırken engellenecek sinyallerin listesi) sıfırlanır, hiçbir sinyali engelleme
    sigaction(SIGINT, &sa, NULL);    // CTRL+C (SIGINT) sinyaline bu yeni handler atanır

    signal(SIGQUIT, SIG_IGN);        // CTRL+\ ignore
	signal(SIGTSTP, SIG_IGN);	  	 // CTRL+Z ignore
}

int	main(void)
{
	char	*line;

	setup_signals();

	while (1)
	{
		// * string literal concatenation
        line = readline(MAGENTA "minismet" BLUE " ¢ " RESET);

		if (!line) // Ctrl+D ile EOF geldi
			break ;

		if (*line)
			add_history(line);

		printf(YELLOW "» " GREEN "%s" RESET "\n", line);
		free(line);
	}

	// Ctrl+D sonrası burada free ve temizleme yapılmalı
	rl_clear_history();

	printf("\n\n" RED "exit" RESET "\n\n");
	return (0);
}
