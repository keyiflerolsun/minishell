/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 15:27:11 by osancak           #+#    #+#             */
/*   Updated: 2025/08/24 10:30:31 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	is_valid_key(char *key)
{
	int	i;

	if (!key || !key[0])
		return (0);
	if (!(ft_isalpha(key[0]) || key[0] == '_'))
		return (0);
	i = -1;
	while (key[++i])
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
			return (0);
	}
	return (1);
}

static void	print_export(t_vars vars)
{
	t_list	*env;
	char	*data;
	int		eq_in_env;

	env = vars.export;
	while (env)
	{
		eq_in_env = 0;
		data = env->data;
		if (ft_strchr(data, '='))
			eq_in_env = 1;
		ft_printf("declare -x ");
		while (*data && *data != '=')
			ft_printf("%c", *data++);
		if (eq_in_env && ft_strstr(data, "comolokko"))
			ft_printf("=\"\"");
		else if (eq_in_env && *++data)
			ft_printf("=\"%s\"", data);
		ft_printf("\n");
		env = env->next;
	}
}

static void	handle_no_equal(char *token, t_vars *vars)
{
	if (is_valid_key(token))
	{
		update_env(&vars->export, token, "");
		delete_env(&vars->env, token);
		vars->last_exit_code = EXIT_SUCCESS;
	}
	else
	{
		write_err(token, "invalid export identifier\n");
		vars->last_exit_code = EXIT_FAILURE;
	}
}

static void	handle_key_value(char *token, t_vars *vars)
{
	char	**parts;

	parts = ft_split(token, '=');
	if (!is_valid_key(parts[0]))
	{
		write_err(parts[0], "invalid export identifier\n");
		vars->last_exit_code = EXIT_FAILURE;
	}
	else
	{
		update_env(&vars->env, parts[0], parts[1]);
		if (parts[1])
			update_env(&vars->export, parts[0], parts[1]);
		else
			update_env(&vars->export, parts[0], "comolokko");
		vars->last_exit_code = EXIT_SUCCESS;
	}
	free_split(parts);
}

void	ft_export(char **tokens, t_vars *vars)
{
	if (!tokens[1])
	{
		print_export(*vars);
		vars->last_exit_code = EXIT_SUCCESS;
		return ;
	}
	if (*tokens[1] == '-')
	{
		write_err("export", "options are not supported\n");
		vars->last_exit_code = 42;
		return ;
	}
	while (*++tokens)
	{
		if (ft_strchr(*tokens, '='))
			handle_key_value(*tokens, vars);
		else
			handle_no_equal(*tokens, vars);
	}
}
