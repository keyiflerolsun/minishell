/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:08:19 by osancak           #+#    #+#             */
/*   Updated: 2025/08/18 12:02:58 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "core.h"

void	error_exit(const char *msg, int exit_code);
int		builtin_exec(t_vars *vars, char **cmd);
pid_t	child_exec(t_vars *vars, char **cmd);
void	pars_to_exec(t_vars *vars);

#endif
