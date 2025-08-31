/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:42:41 by osancak           #+#    #+#             */
/*   Updated: 2025/08/31 19:36:45 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*get_env_value(char **envp, char *key)
{
	size_t	len;
	int		i;

	len = ft_strlen(key);
	i = 0;
	while (envp && envp[i])
	{
		if (!strncmp(envp[i], key, len) && envp[i][len] == '=')
			return (ft_strdup(envp[i] + len + 1));
		i++;
	}
	return (NULL);
}

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->limiter = NULL;
	cmd->append = 0;
	cmd->here_doc = 0;
	return (cmd);
}

static void	free_single_cmd(void *data)
{
	t_cmd	*cmd;

	if (!data)
		return ;
	cmd = (t_cmd *)data;
	if (cmd->args)
		free(cmd->args);
	free(cmd);
}

void	free_cmd(t_vars *vars)
{
	if (vars->cmds)
	{
		ft_lstclear(&vars->cmds, free_single_cmd);
		vars->cmds = NULL;
	}
}

int	count_args(char **args, int i)
{
	int	count;

	count = 0;
	while (args[i] && (is_quoted_token(args[i]) || ft_strcmp(args[i], "|")))
	{
		if (!is_quoted_token(args[i]) && ((!ft_strcmp(args[i], "<")
					|| !ft_strcmp(args[i], ">") || !ft_strcmp(args[i], ">>")
					|| !ft_strcmp(args[i], "<<"))) && args[i + 1])
			i += 2;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}
