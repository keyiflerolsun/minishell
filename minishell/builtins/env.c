/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:48:54 by osancak           #+#    #+#             */
/*   Updated: 2025/08/17 13:03:41 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	*make_env_prefix(char *key, int *len)
{
	char	*prefix;

	prefix = ft_strjoin(key, "=", 0);
	if (len)
		*len = ft_strlen(prefix);
	return (prefix);
}

char	*get_env(t_list *env, char *str)
{
	char	*prefix;
	int		len;

	prefix = make_env_prefix(str, &len);
	while (env)
	{
		if (!ft_strncmp(env->data, prefix, len))
			return (free(prefix), ft_strdup(env->data + len));
		env = env->next;
	}
	return (free(prefix), NULL);
}

void	update_env(t_list **env, char *key, char *value)
{
	t_list	*stack;
	char	*prefix;
	int		len;

	stack = *env;
	prefix = make_env_prefix(key, &len);
	while (stack)
	{
		if (!ft_strncmp(stack->data, prefix, len))
		{
			free(stack->data);
			stack->data = ft_strjoin(prefix, value, 1);
			return ;
		}
		stack = stack->next;
	}
	ft_lstadd_back(env, ft_lstnew(ft_strjoin(prefix, value, 1)));
}

void	delete_env(t_list **env, char *key)
{
	char	*prefix;
	int		len;
	t_list	*to_del;

	prefix = make_env_prefix(key, &len);
	while (*env)
	{
		if (!ft_strncmp((*env)->data, prefix, len))
		{
			to_del = *env;
			*env = (*env)->next;
			free(to_del->data);
			free(to_del);
			free(prefix);
			return ;
		}
		env = &(*env)->next;
	}
	free(prefix);
}

void	ft_env(char **tokens, t_vars *vars)
{
	t_list	*env;

	if (tokens[1])
	{
		write_err("env", "options or arguments are not supported\n");
		vars->last_exit_code = 42;
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
