/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:25:11 by osancak           #+#    #+#             */
/*   Updated: 2025/06/16 02:13:44 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_flag(char c, va_list arg_p)
{
	int		steps;
	size_t	ptr;

	steps = 0;
	if (c == 'c')
		steps += ft_putchr(va_arg(arg_p, int));
	else if (c == 's')
		steps += ft_putstr(va_arg(arg_p, char *));
	else if (c == 'd' || c == 'i')
		steps += ft_putnbr(va_arg(arg_p, int), DECIMAL, 0);
	else if (c == 'u')
		steps += ft_putnbr(va_arg(arg_p, unsigned int), DECIMAL, 1);
	else if (c == 'x')
		steps += ft_putnbr(va_arg(arg_p, unsigned int), HEXA_DOWN, 1);
	else if (c == 'X')
		steps += ft_putnbr(va_arg(arg_p, unsigned int), HEXA_UP, 1);
	else if (c == 'p')
	{
		ptr = va_arg(arg_p, size_t);
		if (!ptr)
			steps += ft_putstr("(nil)");
		else
			steps += ft_putstr("0x") + ft_putnbr(ptr, HEXA_DOWN, 1);
	}
	return (steps);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg_p;
	int		steps;

	steps = 0;
	va_start(arg_p, format);
	while (*format)
	{
		if (*format != '%')
			steps += ft_putchr(*format++);
		else if (*(format + 1) == '%' && format++)
			steps += ft_putchr(*format++);
		else if (format++)
			steps += ft_flag(*format++, arg_p);
	}
	va_end(arg_p);
	return (steps);
}
