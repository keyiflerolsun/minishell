/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:51:46 by osancak           #+#    #+#             */
/*   Updated: 2025/08/08 17:26:04 by osancak          ###   ########.fr       */
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
#include <stdlib.h>

int	main(void)
{
	char	*line;

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
