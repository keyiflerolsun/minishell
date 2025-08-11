/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:21:59 by osancak           #+#    #+#             */
/*   Updated: 2025/08/11 15:24:11 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	write_err(char *left, char *right)
{
	write(STDERR_FILENO, RED, ft_strlen(RED));
	write(STDERR_FILENO, BOLD, ft_strlen(BOLD));
	write(STDERR_FILENO, "[!] ", 4);
	write(STDERR_FILENO, left, ft_strlen(left));
	write(STDERR_FILENO, " : ", 3);
	write(STDERR_FILENO, YELLOW, ft_strlen(YELLOW));
	write(STDERR_FILENO, right, ft_strlen(right));
}
