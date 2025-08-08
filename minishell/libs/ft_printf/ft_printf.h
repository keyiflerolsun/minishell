/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:27:30 by osancak           #+#    #+#             */
/*   Updated: 2025/07/07 13:01:26 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "libft.h"

# define DECIMAL "0123456789"
# define HEXA_UP "0123456789ABCDEF"
# define HEXA_DOWN "0123456789abcdef"

# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;36m"
# define RED "\033[0;31m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define BOLD "\033[1m"
# define RESET "\033[0m"

int	ft_printf(const char *format, ...);
int	ft_putchr(char c);
int	ft_putstr(char *str);
int	ft_putnbr(long long nbr, char *base, int is_unsigned);

#endif
