/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkhalid <bkhalid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 19:26:39 by bkhalid           #+#    #+#             */
/*   Updated: 2025/12/01 17:54:34 by bkhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	p = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!p)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		p[i + j] = s2[j];
		j++;
	}
	p[i + j] = '\0';
	return (p);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			return ((char *)s + i);
		}
		i++;
	}
	if ((char)c == '\0')
	{
		return ((char *)s + i);
	}
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		p = malloc(1);
		p[0] = '\0';
		return (p);
	}
	if (len > ft_strlen(&s[start]))
		len = ft_strlen(&s[start]);
	p = malloc(len + 1);
	if (!p)
		return (NULL);
	while (i < len)
		p[i++] = s[start++];
	p[i] = '\0';
	return (p);
}
