/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 22:23:46 by osancak           #+#    #+#             */
/*   Updated: 2025/08/11 16:10:15 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

// 🖨️ Standart IO
# include <stdio.h>  // printf, perror
# include <string.h> // strerror

// 🧠 GNU Readline
# include <readline/history.h>  // add_history
# include <readline/readline.h> // readline, rl_*

// 🧠 Memory
# include <limits.h> // sys limits
# include <stdlib.h> // malloc, free, exit, getenv

// 🔧 Sys Calls
# include <fcntl.h>     // open
# include <sys/stat.h>  // stat, lstat, fstat, unlink
# include <sys/types.h> // stat yapıları
// write, access, read, close, fork, execve, dup*, pipe, isatty, tty*
# include <unistd.h>

// 🧒 Processes
# include <errno.h>    // errno
# include <signal.h>   // signal, sigaction, sigemptyset, sigaddset, kill
# include <sys/wait.h> // wait, waitpid, wait3, wait4

// 📂 *dir
# include <dirent.h> // opendir, readdir, closedir

// 🧭 Cwd
# include <unistd.h> // getcwd, chdir

// 🖥️ Terminal Control
# include <sys/ioctl.h> // ioctl
# include <unistd.h>    // isatty, ttyname, ttyslot

// 🧵 Terminal Attr
# include <termios.h> // tcgetattr, tcsetattr

// 🧾 Termcap
# include <termcap.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;36m"
# define RED "\033[0;31m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define BOLD "\033[1m"
# define RESET "\033[0m"

size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_strstr(const char *big, const char *little);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strdup(const char *s);

#endif
