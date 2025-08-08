/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:01:16 by osancak           #+#    #+#             */
/*   Updated: 2025/08/08 18:11:49 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXECUTER_H
# define FT_EXECUTER_H

# include "pipex.h"

pid_t	ft_execute(t_pipe vars, char *command, char **envp);

#endif
