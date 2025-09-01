/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:08:15 by osancak           #+#    #+#             */
/*   Updated: 2025/09/01 10:31:31 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "utils.h"

typedef struct s_vars
{
	char	**ep;
	t_list	*env;
	t_list	*export;
	char	**path;
	char	**tokens;
	t_list	*cmds;
	int		last_exit_code;
	int		tmp;
	char	**_tmp;
}			t_vars;

void		setup_signals(void);
void		set_path(t_vars *vars);
char		*get_path(char **path, char *command);
void		free_split(char **split_data);
void		init_shell(t_vars *vars, char **ep);
void		ft_clear(void);
t_vars		*static_vars(t_vars *vars);
void		update_vars(t_vars *vars);

#endif
