/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:52:41 by osancak           #+#    #+#             */
/*   Updated: 2025/08/31 17:03:14 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_vars	*static_vars(t_vars *vars)
{
	static t_vars	*s_vars;

	if (vars)
		s_vars = vars;
	return (s_vars);
}

static void	sort_list(t_list *lst)
{
	t_list	*ptr;
	void	*tmp;
	int		flag;

	flag = 1;
	while (flag)
	{
		flag = 0;
		ptr = lst;
		while (ptr && ptr->next)
		{
			if (ft_strcmp((char *)ptr->data, (char *)ptr->next->data) > 0)
			{
				tmp = ptr->data;
				ptr->data = ptr->next->data;
				ptr->next->data = tmp;
				flag = 1;
			}
			ptr = ptr->next;
		}
	}
}

static void	env2p(t_vars *vars)
{
	t_list	*env;
	char	**ep;
	int		i;

	free(vars->ep);
	env = vars->env;
	ep = ft_calloc(sizeof(char *), ft_lstsize(env) + 1);
	i = -1;
	while (env)
	{
		ep[++i] = env->data;
		env = env->next;
	}
	vars->ep = ep;
	set_path(vars);
	vars->tmp = 0;
	static_vars(vars);
}

void	update_vars(t_vars * vars)
{
	sort_list(vars->export);
	sort_list(vars->env);
	env2p(vars);
}
