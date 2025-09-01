/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:24:09 by osancak           #+#    #+#             */
/*   Updated: 2025/09/01 11:00:46 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int	main(int ac, char **av, char **ep)
{
	t_vars	vars;

	(void)ac, (void)av;
	init_shell(&vars, ep);
	return (vars.last_exit_code);
}
