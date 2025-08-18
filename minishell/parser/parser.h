/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:08:26 by osancak           #+#    #+#             */
/*   Updated: 2025/08/18 13:51:13 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "core.h"

typedef struct s_cmd
{
	char		**args;
	char		*infile;
	char		*outfile;
	int			append;
	int			here_doc;
	char		*limiter;
}				t_cmd;

typedef struct s_token_array
{
	char		**tokens;
	int			size;
	int			capacity;

}				t_token_array;

void			handle_token(t_token_array *arr, const char *input, int *i);
void			handle_metachar(t_token_array *arr, const char *input, int *i);
t_token_array	*init_token(t_token_array *arr);
char			*make_token(const char *input, int start, int end);
void			add_token(t_token_array *arr, char *token);
char			**quote_aware_split(const char *input);
char			*get_env_value(char **envp, char *key);
void			ft_parser(t_vars *vars, char *line);
char			*expand_env(t_vars vars, const char *line);
t_cmd			*init_cmd(void);
void			parse_cmd(t_vars *vars, char **args, int *i);
void			free_cmd(t_vars *vars);

#endif
