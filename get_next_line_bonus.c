/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkhalid <bkhalid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 19:26:42 by bkhalid           #+#    #+#             */
/*   Updated: 2025/12/01 17:53:49 by bkhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*filter(char *buffer)
{
	int		i;
	int		j;
	char	*line;

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

char	*update_stock(char *stock)
{
	int		i;
	char	*new_stock;

	if (!stock)
		return (NULL);
	i = 0;
	while (stock[i] && stock[i] != '\n')
		i++;
	if (!stock[i])
	{
		free(stock);
		return (NULL);
	}
	new_stock = ft_substr(stock, i + 1, ft_strlen(stock) - (i + 1));
	free(stock);
	return (new_stock);
}

static char	*check_offset(int y, char *stock)
{
	if (y <= 0)
	{
		if (!stock || *stock == '\0')
			return (NULL);
		return (filter(stock));
	}
	return (stock);
}

static char	*read_part(int fd, char *stock, char *x)
{
	ssize_t	y;
	char	*result;
	char	*c;

	y = read(fd, x, BUFFER_SIZE);
	if (y < 0)
		return (NULL);
	while (y)
	{
		result = check_offset(y, x);
		if (!result)
			return (NULL);
		if (y == 0)
			return (result);
		x[y] = '\0';
		c = stock;
		stock = ft_strjoin(stock, x);
		free(c);
		if (stock && ft_strchr(stock, '\n'))
			break ;
		y = read(fd, x, BUFFER_SIZE);
	}
	return (stock);
}

char	*get_next_line(int fd)
{
	static char	*stock[1024];
	char		*x;
	char		*result;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	x = malloc(BUFFER_SIZE + 1);
	if (!x)
		return (NULL);
	stock[fd] = read_part(fd, stock[fd], x);
	free(x);
	if (!stock[fd] || *stock[fd] == '\0')
		return (NULL);
	result = filter(stock[fd]);
	stock[fd] = update_stock(stock[fd]);
	return (result);
}
