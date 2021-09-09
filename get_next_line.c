/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsarri-c <rsarri-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 09:51:58 by rsarri-c          #+#    #+#             */
/*   Updated: 2021/09/09 13:27:17 by rsarri-c         ###   ########.fr       */
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

	i = 0;
	while (str[i++])
	{
		if (str[i] == '\n')
			break ;
	}
	line = malloc(i + 1);
	if (!line)
		return (0);
	i = 0;
	while (str[i])
	{
		line[i] = str[i];
		if (str[i] == '\n')
		{
			i++;
			break ;
		}
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

/*int main()
{
	int	fd;
	int	fd2;
	int fd3;
	char *line;
	char *line2;
	char *line3;
	fd = open("./gnlTester/files/42_no_nl", O_RDONLY);
	fd2 = open("./gnlTester/files/empty", O_RDONLY);
	fd3 = open("./gnlTester/files/nl", O_RDONLY);
	line = get_next_line(fd);
	printf("l1: %s", line);
	line2 = get_next_line(fd2);
	printf("l2: %s", line2);
	line3 = get_next_line(fd3);
	printf("l3: %s", line3);
	while (line != NULL || line2 != NULL || line3 != NULL)
	{
		if (line != NULL)
		{
			printf("l1: %s", line);
			free(line);
			line = get_next_line(fd);
		}
		if (line2 != NULL)
		{
			printf("l2: %s", line2);
			free(line2);
			line2 = get_next_line(fd2);
		}
		if (line3 != NULL)
		{
			printf("l3: %s", line3);
			free(line3);
			line3 = get_next_line(fd3);
		}
	}
	//printf("%s", line);
	//free(line);
	close(fd);
	close(fd2);
	close(fd3);
	//system("leaks -q a.out");
	return (0);
}*/
