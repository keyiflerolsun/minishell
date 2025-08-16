/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:46:28 by osancak           #+#    #+#             */
/*   Updated: 2025/08/16 12:24:14 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	is_possible(const char *str)
{
	if (!str || !*str)
		return (0);
	while (*str)
		if (!ft_isdigit(*str++))
			return (0);
	return (1);
}

int	ft_atoi(const char *nptr, int *res)
{
	long int	toi;
	int			sig;

	sig = 1;
	toi = 0;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			sig *= -1;
	if (!is_possible(nptr))
		return (0);
	while (*nptr && ft_isdigit(*nptr))
	{
		toi = toi * 10;
		if (toi >= 2147483647)
			return (0);
		toi += (*nptr++ - '0');
	}
	if (toi * sig > 2147483647 || toi * sig < -2147483648)
		return (0);
	*res = toi * sig;
	return (1);
}
