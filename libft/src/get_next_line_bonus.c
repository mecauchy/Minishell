/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:55:21 by vluo              #+#    #+#             */
/*   Updated: 2024/11/29 18:27:35 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	free_buf(char *buf, int start)
{
	int	i;

	i = start;
	while (i < BUFFER_SIZE + 1)
		buf[i ++] = '\0';
}

void	bufmove(char *buf, int i)
{
	int	buf_length;
	int	ibis;
	int	ind;

	if (buf[0] == '\0')
		return ;
	if (buf[i - 1] != '\n')
		buf_length = i;
	else
	{
		ibis = i - 1;
		while (buf[ibis])
			ibis ++;
		buf_length = ibis;
	}
	ind = 0;
	while (ind < buf_length - i)
	{
		buf[ind] = buf[ind + i];
		ind ++;
	}
	free_buf(buf, ind);
}

int	go_to_endl(char *buf)
{
	int	i;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i ++;
	return (i);
}

char	*get_next_line(int fd)
{
	static char	buf[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*line;
	int			i;

	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE <= 0)
		return (0);
	line = 0;
	i = go_to_endl(buf[fd]);
	line = ft_strnjoin(line, buf[fd], i + 1);
	bufmove(buf[fd], i + 1);
	if (line != 0 && line[i] == '\n')
		return (line);
	while (read(fd, buf[fd], BUFFER_SIZE) > 0)
	{
		i = go_to_endl(buf[fd]);
		line = ft_strnjoin(line, buf[fd], i + 1);
		if (buf[fd][i] == '\n')
		{
			bufmove(buf[fd], i + 1);
			break ;
		}
		free_buf(buf[fd], 0);
	}
	return (line);
}

// #include <fcntl.h>
// int main(int argc, char **argv)
// {
// 	// int fd = open(argv[1], O_RDWR);
// 	// close(fd);
// 	// char *line = get_next_line(fd);
// 	// printf("%s", line);
// 	// line = get_next_line(fd);
// 	// printf("%s", line);

// 	int fd = open(argv[1], O_RDONLY);
// 	char *line = get_next_line(fd);
// 	while (line != 0)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	argv[0] ++;
// 	return (argc * 0);
// }
