/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:20:39 by osancak           #+#    #+#             */
/*   Updated: 2025/08/14 19:42:34 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_pwd(char *line)
{
	char	buff[PATH_MAX];

	if (ft_strlen(line) != 3)
	{
		write_err("pwd", "options or arguments are not supported\n");
		return ;
	}
	getcwd(buff, sizeof(buff));
	ft_printf("%s\n", buff);
}
