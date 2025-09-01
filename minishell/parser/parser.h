/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:08:26 by osancak           #+#    #+#             */
/*   Updated: 2025/08/31 17:22:11 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "core.h"

# define ARG_PIPE_SEPARATOR '\x1D'

typedef struct s_expander
{
	int			q[2];
	char		*res;
	char		tmp[2];
	size_t		i;
}				t_expander;

typedef struct s_cmd
{
	char		**args;
	char		*infile;
	char		*outfile;
	int			append;
	int			here_doc;
	char		**limiters;
	int			heredoc_count;
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
int				count_args(char **args, int i);
int				is_quoted_token(char *token);
char			*strip_quote(char *token);
void			add_quoted_token(char **merged, char *tmp);
void			handle_quoted_part(const char *input, int *i, char **merged);
void			handle_unquoted_part(const char *input, int *i, char **merged);
int				is_sd(char c);
int				ft_is_op(char c);
int				check_outfile(char **args);
int				is_heredot(const char *line, size_t d_i);
int				cont_meta(t_vars *vars, char **args);
int				add_heredoc_limiter(t_cmd *cmd, char *limiter);

#endif
