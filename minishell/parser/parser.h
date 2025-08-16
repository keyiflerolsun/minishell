/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:08:26 by osancak           #+#    #+#             */
/*   Updated: 2025/08/16 20:47:58 by osancak          ###   ########.fr       */
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
t_token_array	*init_token(t_token_array *arr);
char			*make_token(const char *input, int start, int end);
void			add_token(t_token_array *arr, char *token);
char			**quote_aware_split(const char *input);
char			*parser_join(char *s1, char *s2);
char			*get_env_value(char **envp, char *key);
void			ft_parser(t_vars *vars, char *line);
char			*expand_env(t_vars vars, const char *line, char **envp);

#endif
