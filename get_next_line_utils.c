/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsarri-c <rsarri-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 09:52:04 by rsarri-c          #+#    #+#             */
/*   Updated: 2021/09/09 08:10:10 by rsarri-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*tmp;
	size_t	i;
	size_t	j;
	size_t	tot_len;

	tot_len = ft_strlen(s1) + ft_strlen(s2);
	if (!tot_len)
		return (0);
	tmp = malloc(tot_len + 1);
	if (!tmp)
		return (0);
	i = 0;
	j = 0;
	if (s1)
	{
		while (i < tot_len && s1[j])
			tmp[i++] = s1[j++];
	}
	j = 0;
	while (i < tot_len && s2[j])
		tmp[i++] = s2[j++];
	tmp[i] = '\0';
	free((char *)s1);
	return (tmp);
}
