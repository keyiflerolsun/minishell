/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:08:19 by osancak           #+#    #+#             */
/*   Updated: 2025/08/09 14:51:31 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "core.h"

void	error_exit(const char *msg, int exit_code);
pid_t	ft_execute(t_vars vars, char *command);

#endif
