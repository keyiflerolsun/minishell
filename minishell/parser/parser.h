/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:08:26 by osancak           #+#    #+#             */
/*   Updated: 2025/08/11 16:33:38 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "core.h"

typedef struct s_command
{
	char		**cmd_args;
}				t_command;

typedef struct s_token_array
{
	char		**tokens;
	int			size;
	int			capacity;

}				t_token_array;

void			add_token(t_token_array *arr, char *token);
char			**quote_aware_split(const char *input);
char			*process_token(char *token);
char			*ft_strjoin_three(char first, char *middle, char last);
t_token_array	*init_token(t_token_array *arr);
int				ft_isspace(int c);
void			ft_parser(t_vars *vars, char *line);

#endif
