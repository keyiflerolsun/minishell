/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:03:37 by osancak           #+#    #+#             */
/*   Updated: 2025/07/22 10:28:40 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	free_str(char *s1, char *s2, int which_free)
{
	if (which_free == 1)
		free(s1);
	if (which_free == 2)
		free(s2);
	if (which_free == 3)
	{
		free(s1);
		free(s2);
	}
}

char	*gnl_strjoin(char *s1, char *s2, int which_free)
{
	char	*res;
	char	*ss1;
	char	*ss2;
	int		i;

	if (!*s1 && !*s2)
		return (ft_calloc(1, sizeof(char)));
	ss1 = s1;
	ss2 = s2;
	res = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (*s1)
		res[i++] = *s1++;
	while (*s2)
		res[i++] = *s2++;
	free_str(ss1, ss2, which_free);
	return (res);
}
