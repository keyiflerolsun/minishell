/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:08:12 by osancak           #+#    #+#             */
/*   Updated: 2025/08/16 13:44:03 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "core.h"

void	write_err(char *left, char *right);
void	ft_pwd(char *line);
char	*get_env(t_vars vars, char *str);
void	ft_env(char *line, t_vars vars);
void	ft_echo(char **tokens, t_vars vars);

#endif
