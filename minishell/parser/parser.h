/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:08:26 by osancak           #+#    #+#             */
/*   Updated: 2025/08/14 18:46:33 by osancak          ###   ########.fr       */
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

int				ft_isspace(int c);
int				is_metachar(char c);
void			handle_token(t_token_array *arr, const char *input, int *i);
void			handle_metachar(t_token_array *arr, const char *input, int *i);
void			handle_unquoted_part(const char *input, int *i, char **merged);
void			handle_quoted_part(const char *input, int *i, char **merged);
t_token_array	*init_token(t_token_array *arr);
char			*make_token(const char *input, int start, int end);
void			add_token(t_token_array *arr, char *token);
char			**quote_aware_split(const char *input);
char			*ft_strjoin_three(char first, char *middle, char last);
void			ft_parser(t_vars *vars, char *line);
char			*expand_env(const char *line, char **envp);

#endif
