/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsarri-c <rsarri-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 09:51:58 by rsarri-c          #+#    #+#             */
/*   Updated: 2021/09/18 17:51:21 by rsarri-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

char	*get_storage(char *storage)
{
	char	*tmp_storage;
	size_t	i;
	size_t	j;

	if (!storage)
		return (0);
	i = 0;
	while (storage[i] && storage[i] != '\n')
		i++;
	if (storage[i] == '\n')
		i++;
	if (!storage[i])
	{
		free(storage);
		return (0);
	}
	tmp_storage = (char *)malloc(ft_strlen(storage) - i + 1);
	if (!tmp_storage)
		return (0);
	j = 0;
	while (storage[i])
		tmp_storage[j++] = storage[i++];
	tmp_storage[j] = '\0';
	free(storage);
	return (tmp_storage);
}

char	*get_line(char *str)
{
	size_t	i;
	char	*line;
	int		flag;

	i = 0;
	flag = 0;
	while (str[i++] != '\0' && flag == 0)
	{
		if (str[i] == '\n')
			flag = 1;
	}
	line = malloc(i + 1);
	if (!line)
		return (0);
	i = 0;
	flag = 0;
	while (str[i] != '\0' && flag == 0)
	{
		line[i] = str[i];
		if (str[i] == '\n')
			flag = 1;
		i++;
	}
	line[i] = '\0';
	return (line);
}

size_t	check_isnline(char *str)
{
	size_t	nline;

	if (!str)
		return (0);
	nline = 0;
	while (*str != '\0' && nline == 0)
	{
		if (*str == '\n')
			nline = 1;
		str++;
	}
	return (nline);
}

int	check_read(int read, char *tmp)
{
	int	res;

	res = 0;
	if (read == -1)
	{
		free(tmp);
		return (res);
	}
	res = 1;
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;
	char		*tmp;
	size_t		rs;

	tmp = malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	rs = 1;
	while (rs > 0 && !check_isnline(storage))
	{
		rs = read(fd, tmp, BUFFER_SIZE);
		if (check_read(rs, tmp) == 0)
			return (0);
		if (rs == 0)
			break ;
		tmp[rs] = '\0';
		storage = ft_strjoin(storage, tmp);
	}
	free(tmp);
	if (!storage)
		return (0);
	line = get_line(storage);
	storage = get_storage(storage);
	return (line);
}

/*void bye()
{
	system("leaks -q a.out");
}
int main(int argc, char **argv)
{
	int	fd;
	int i = 0;
	char *line;
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line != NULL)
		{
			printf("l%d: %s",  i++,line);
			free(line);
			line = get_next_line(fd);
		}
	}
	close(fd);
	atexit(bye);
	return (0);
}*/