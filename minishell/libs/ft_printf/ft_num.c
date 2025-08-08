/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:36:29 by osancak           #+#    #+#             */
/*   Updated: 2025/07/03 13:30:38 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(long long nbr, char *base, int is_unsigned)
{
	int					res;
	size_t				rad;
	unsigned long long	num;

	res = 0;
	rad = ft_strlen(base);
	if (!is_unsigned && nbr < 0)
	{
		res += ft_putchr('-');
		num = -nbr;
	}
	else
		num = (unsigned long long)nbr;
	if (num >= rad)
	{
		res += ft_putnbr(num / rad, base, is_unsigned);
		res += ft_putnbr(num % rad, base, is_unsigned);
	}
	else
		res += ft_putchr(base[num]);
	return (res);
}
