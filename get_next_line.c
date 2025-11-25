/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkhalid <bkhalid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 16:40:49 by bkhalid           #+#    #+#             */
/*   Updated: 2025/11/25 11:07:33 by bkhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
char	*ft_strdup(const char *s)
{
	char	*p;
	int		i;
	int		len_s;

	len_s = ft_strlen(s);
	p = malloc(len_s + 1);
	if (!p)
		return (NULL);
	i = 0;
	while (i < len_s)
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	len_s1;
	size_t	len_s2;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	j = len_s1 + len_s2;
	p = malloc(j + 1);
	if (!p)
		return (NULL);
	ft_memcpy(p, s1, len_s1);
	ft_memcpy(p + len_s1, s2, len_s2);
	p[j] = '\0';
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
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
static char	*filter(char *buffer)
{
	int		i;
	int		j;
	int		p;
	char	*line;

	p = 0;
	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = buffer[j];
		j++;
	}
	if (buffer[i] == '\n')
	{
		line[j] = '\n';
		j++;
	}
	line[j] = '\0';
	return (line);
}
static char	*update_stock(char *stock)
{
	int		i;
	int		j;
	int		len;
	char	*new_stock;

	i = 0;
	if (!stock)
		return (NULL);
	while (stock[i] && stock[i] != '\n')
		i++;
	if (!stock[i])
	{
		free(stock);
		return (NULL);
	}
	len = ft_strlen(stock);
	new_stock = malloc(len - i);
	if (!new_stock)
	{
		free(stock);
		return (NULL);
	}
	j = 0;
	i++;
	while (stock[i])
		new_stock[j++] = stock[i++];
	new_stock[j] = '\0';
	free(stock);
	return (new_stock);
}

char	*check_offset(int y, char *stock)
{
	char	*c;

	if (y <= 0)
	{
		if (!stock || *stock == '\0')
		{
			free(stock);
			stock = NULL;
			return (NULL);
		}
		c = filter(stock);
		stock = update_stock(stock);
		return (c);
	}
	return (stock);
}
char	*get_next_line(int fd)
{
	static char	*stock;
	ssize_t		y;
	char		*c;
	char		*x;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	x = malloc(BUFFER_SIZE + 1);
	if (!x)
		return (NULL);
	y = read(fd, x, BUFFER_SIZE);
	if (y < 0)
		return (NULL);
	while (y)
	{
		if (stock && ft_strchr(stock, '\n'))
			break ;
		char *result = check_offset(y, x);
		if (!result)
			return (free(x), NULL);
		if (y == 0)
			return (result);
		else
		{
			x[y] = '\0';
			stock = ft_strjoin(stock, x);
			free(x);
		}
		y = read(fd, x, BUFFER_SIZE);
	}
	free(x);
	c = filter(stock);
	stock = update_stock(stock);
	return (c);
}

#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	line = get_next_line(fd);
	//printf("%s", line);
	while (line)
	{
		printf("%s\n", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
