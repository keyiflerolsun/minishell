/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:08:15 by osancak           #+#    #+#             */
/*   Updated: 2025/08/16 13:43:34 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "utils.h"

typedef struct s_vars
{
	char	**ep;
	t_list	*env;
	char	**path;
	int		last_exit_code;
}			t_vars;

void		setup_signals(void);
void		set_path(t_vars *vars);
char		*get_path(char **path, char *command);
void		free_split(char **split_data);
void		init_shell(t_vars *vars, char **ep);

#endif
