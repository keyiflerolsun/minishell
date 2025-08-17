/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 22:23:46 by osancak           #+#    #+#             */
/*   Updated: 2025/08/17 10:11:47 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

// 🖨️ Standart IO
# include <stdio.h> // perror

// 🧠 Bellek & Temel Türler
# include <stdarg.h> // va_list (ft_printf)
# include <stddef.h> // size_t
# include <stdlib.h> // malloc, free, exit

// 🧠 GNU Readline
# include <readline/history.h>  // add_history
# include <readline/readline.h> // readline, rl_*

// 🔧 Sys Calls
# include <fcntl.h>    // open
# include <sys/stat.h> // unlink
# include <unistd.h>   // write, access, read, close, fork, execve, dup*

// 🧒 Processes & Sinyaller
# include <errno.h>    // errno
# include <signal.h>   // signal*
# include <sys/wait.h> // wait*

// 🎨 Metin Renkleri
# define BLACK      "\033[0;30m"
# define RED        "\033[0;31m"
# define GREEN      "\033[0;32m"
# define YELLOW     "\033[0;33m"
# define BLUE       "\033[0;34m"
# define MAGENTA    "\033[0;35m"
# define CYAN       "\033[0;36m"
# define WHITE      "\033[0;37m"

// 🎨 Kalın Metin Renkleri
# define BOLD_BLACK     "\033[1;30m"
# define BOLD_RED       "\033[1;31m"
# define BOLD_GREEN     "\033[1;32m"
# define BOLD_YELLOW    "\033[1;33m"
# define BOLD_BLUE      "\033[1;34m"
# define BOLD_MAGENTA   "\033[1;35m"
# define BOLD_CYAN      "\033[1;36m"
# define BOLD_WHITE     "\033[1;37m"

// 🎨 Arka Plan Renkleri
# define BG_BLACK   "\033[40m"
# define BG_RED     "\033[41m"
# define BG_GREEN   "\033[42m"
# define BG_YELLOW  "\033[43m"
# define BG_BLUE    "\033[44m"
# define BG_MAGENTA "\033[45m"
# define BG_CYAN    "\033[46m"
# define BG_WHITE   "\033[47m"

// 🎨 Stil Kodları
# define BOLD       "\033[1m"
# define DIM        "\033[2m"
# define UNDERLINE  "\033[4m"
# define BLINK      "\033[5m"
# define REVERSE    "\033[7m"
# define HIDDEN     "\033[8m"

// 🔄 Sıfırlama
# define RESET      "\033[0m"
# define RESET_BG   "\033[49m"
# define RESET_FG   "\033[39m"

// 🔢 ft_printf sabitleri
# define DECIMAL    "0123456789"
# define HEXA_UP    "0123456789ABCDEF"
# define HEXA_DOWN  "0123456789abcdef"

// 🔗 Veri Yapıları
typedef struct s_list
{
	void			*data;
	struct s_list	*next;
}					t_list;

// 🔤 Karakter / Sınıflandırma
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isspace(int c);
int					ft_ismeta(char c);

// 🔁 Dönüşüm
int					ft_atoi(const char *nptr, int *res);
char				*ft_itoa(int n);

// 🔎 Uzunluk / Karşılaştırma / Arama
size_t				ft_strlen(const char *s);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strstr(const char *big, const char *little);
char				*ft_strchr(const char *s, int c);

// 🧽 Bellek ve Kopyalama
void				*ft_calloc(size_t nmemb, size_t size);
void				*ft_memcpy(void *dest, const void *src, size_t n);
char				*ft_strdup(const char *s);

// ✂️ String Parçalama/Birleştirme
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				**ft_split(char const *s, char c);
char				*ft_strjoin(char *s1, char *s2, int which_free);
char				*ft_strtrim(char const *s1, char const *set);

// 🖨️ Yazdırma / ft_printf
int					ft_putchr(char c);
int					ft_putstr(char *str);
int					ft_putnbr(long long nbr, char *base, int is_unsigned);
int					ft_printf(const char *format, ...);

// 🔗 Bağlı Liste Yardımcıları
t_list				*ft_lstnew(void *data);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
int					ft_lstsize(t_list *lst);

#endif
