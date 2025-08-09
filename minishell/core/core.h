/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:08:15 by osancak           #+#    #+#             */
/*   Updated: 2025/08/09 14:51:42 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "utils.h"

typedef struct s_vars
{
	char	**ep;
	char	**path;
}			t_vars;

void		setup_signals(void);
void		set_path(t_vars *vars);
char		*get_path(char **path, char *command);
void		free_path(char **path);
void		init_shell(t_vars *vars, char **ep);

#endif
