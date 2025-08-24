/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:52:41 by osancak           #+#    #+#             */
/*   Updated: 2025/08/24 10:52:54 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	sort_list(t_list *lst)
{
	t_list	*ptr;
	void	*tmp;
	int		flag;

	flag = 1;
	while (flag)
	{
		flag = 0;
		ptr = lst;
		while (ptr && ptr->next)
		{
			if (ft_strcmp((char *)ptr->data, (char *)ptr->next->data) > 0)
			{
				tmp = ptr->data;
				ptr->data = ptr->next->data;
				ptr->next->data = tmp;
				flag = 1;
			}
			ptr = ptr->next;
		}
	}
}
