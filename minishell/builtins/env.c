/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:48:54 by osancak           #+#    #+#             */
/*   Updated: 2025/08/16 13:44:42 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*get_env(t_vars vars, char *str)
{
	t_list	*env;
	char	*tmp;
	int		len;

	env = vars.env;
	if (*str == '$')
		str++;
	tmp = ft_strjoin(str, "=");
	len = ft_strlen(tmp);
	while (env)
	{
		if (!ft_strncmp(env->data, tmp, len))
			return (free(tmp), ft_strdup(env->data + len));
		env = env->next;
	}
	return (free(tmp), NULL);
}

void	ft_env(char *line, t_vars vars)
{
	t_list	*env;

	if (ft_strlen(line) != 3)
	{
		write_err("env", "options or arguments are not supported\n");
		return ;
	}
	env = vars.env;
	while (env)
	{
		ft_printf("%s\n", env->data);
		env = env->next;
	}
}
