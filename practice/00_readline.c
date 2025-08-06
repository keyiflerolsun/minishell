/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:51:46 by osancak           #+#    #+#             */
/*   Updated: 2025/08/06 18:27:36 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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
