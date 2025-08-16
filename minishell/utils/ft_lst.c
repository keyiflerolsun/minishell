/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 18:55:48 by osancak           #+#    #+#             */
/*   Updated: 2025/08/16 14:29:49 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_list	*ft_lstnew(void *data)
{
	t_list	*res;

	res = malloc(sizeof(t_list));
	if (!res)
		return (NULL);
	(*res).data = data;
	res->next = NULL;
	return (res);
}

t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
	{
		if (!(lst->next))
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

int	ft_lstsize(t_list *lst)
{
	int	res;

	res = 0;
	while (lst)
	{
		lst = lst->next;
		res++;
	}
	return (res);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*res;

	if (*lst)
	{
		res = ft_lstlast(*lst);
		res->next = new;
	}
	else
		*lst = new;
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		del((*lst)->data);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}
