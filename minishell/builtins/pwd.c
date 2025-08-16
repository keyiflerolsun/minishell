/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:20:39 by osancak           #+#    #+#             */
/*   Updated: 2025/08/16 15:07:56 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_pwd(char **tokens, t_vars *vars)
{
	char	buff[PATH_MAX];

	if (tokens[1])
	{
		write_err("pwd", "options or arguments are not supported\n");
		vars->last_exit_code = EXIT_FAILURE;
		return ;
	}
	getcwd(buff, sizeof(buff));
	ft_printf("%s\n", buff);
}
