/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:48:54 by osancak           #+#    #+#             */
/*   Updated: 2025/08/16 17:03:41 by osancak          ###   ########.fr       */
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

void	update_env(t_vars *vars, char *key, char *value)
{
	t_list	*env;
	char	*tmp;

	env = vars->env;
	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return ;
	while (env)
	{
		if (!ft_strncmp(env->data, tmp, ft_strlen(tmp)))
		{
			free(env->data);
			env->data = ft_strjoin(tmp, value);
			free(tmp);
			return ;
		}
		env = env->next;
	}
	ft_lstadd_back(&vars->env, ft_lstnew(ft_strjoin(tmp, value)));
	free(tmp);
}

void	delete_env(t_vars *vars, char *key)
{
	t_list	**env;
	char	*tmp;
	t_list	*to_del;

	env = &vars->env;
	tmp = ft_strjoin(key, "=");
	while (*env)
	{
		if (!ft_strncmp((*env)->data, tmp, ft_strlen(tmp)))
		{
			to_del = *env;
			*env = (*env)->next;
			free(to_del->data);
			free(to_del);
			free(tmp);
			return ;
		}
		env = &(*env)->next;
	}
	free(tmp);
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
	vars->last_exit_code = EXIT_SUCCESS;
}
