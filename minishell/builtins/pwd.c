/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:20:39 by osancak           #+#    #+#             */
/*   Updated: 2025/08/16 19:00:54 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_pwd(char **tokens, t_vars *vars)
{
	char	buff[PATH_MAX];

	if (!bi_is_valid(tokens, vars))
		return ;
	getcwd(buff, sizeof(buff));
	ft_printf("%s\n", buff);
	vars->last_exit_code = EXIT_SUCCESS;
}
