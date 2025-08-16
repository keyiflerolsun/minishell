/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:48:54 by osancak           #+#    #+#             */
/*   Updated: 2025/08/16 15:08:12 by osancak          ###   ########.fr       */
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

void	ft_env(char **tokens, t_vars *vars)
{
	t_list	*env;

	if (tokens[1])
	{
		write_err("env", "options or arguments are not supported\n");
		vars->last_exit_code = EXIT_FAILURE;
		return ;
	}
	env = vars->env;
	while (env)
	{
		ft_printf("%s\n", env->data);
		env = env->next;
	}
}
