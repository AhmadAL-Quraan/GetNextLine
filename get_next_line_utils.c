/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqoraan <aqoraan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 21:54:15 by aqoraan           #+#    #+#             */
/*   Updated: 2026/01/01 22:53:23 by aqoraan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*str)
	{
		str += 1;
		len += 1;
	}
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	i;
	size_t	ptr_idx;

	if (!s1 || !s2)
		return (NULL);
	ptr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	ptr_idx = 0;
	while (s1[i])
		ptr[ptr_idx++] = s1[i++];
	i = 0;
	while (s2[i])
		ptr[ptr_idx++] = s2[i++];
	ptr[ptr_idx] = '\0';
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
	{
		return (NULL);
	}
	while (*s)
	{
		if ((unsigned char)*s == (unsigned char)c)
		{
			return ((char *)s);
		}
		s += 1;
	}
	if (*s == c)
	{
		return ((char *)s);
	}
	return (NULL);
}
