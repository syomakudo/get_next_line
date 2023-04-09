/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syoma.k <syoma.k@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:45:21 by syoma.k           #+#    #+#             */
/*   Updated: 2023/04/09 19:00:20 by syoma.k          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// int BUFFER_SIZE = 1;
// callocを使っているのでバッファサイズが大きい時に時間がかかる

char	*join_free(char *line_buf, char *buffer)
{
	char	*reline_buf;

	reline_buf = ft_strjoin(line_buf, buffer);
	free(line_buf);
	line_buf = NULL;
	return (reline_buf);
}

char	*read_gnl(int fd, char *line_buf)
{
	ssize_t	read_num;
	char	*buffer;

	buffer = ft_calloc(BUFFER_SIZE + (size_t)1, sizeof(char));
	read_num = 1;
	while (read_num > 0 && buffer && line_buf)
	{
		if (buffer[0])
			ft_bzero(buffer, BUFFER_SIZE + (size_t)1);
		read_num = read(fd, buffer, BUFFER_SIZE);
		if (read_num < 0)
		{
			free(buffer);
			return (NULL);
		}
		else if (read_num == 0)
			break ;
		line_buf = join_free(line_buf, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	buffer = NULL;
	return (line_buf);
}

char	*push_line(char *line_buf)
{
	char	*reline;
	size_t	i;

	i = 0;
	if (!line_buf[i])
		return (NULL);
	while (line_buf[i] != '\n' && line_buf[i] != '\0')
		i++;
	if (line_buf[i] == '\0')
		i--;
	reline = ft_calloc(i + (size_t)2, sizeof(char));
	if (!reline)
		return (NULL);
	i = 0;
	while (line_buf[i] != '\n' && line_buf[i] != '\0')
	{
		reline[i] = line_buf[i];
		i++;
	}
	if (line_buf[i] == '\n')
		reline[i++] = '\n';
	reline[i] = '\0';
	return (reline);
}

//以下の条件式のNULLを変えるif (!line_buf[i] || !line_buf[i + 1])
char	*next_line(char *line_buf)
{
	char	*next_buf;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (line_buf[i] != '\n' && line_buf[i] != '\0')
		i++;
	if (!line_buf[i] || !line_buf[i + 1])
	{
		free(line_buf);
		line_buf = NULL;
		return ("EndOfFile");
	}
	next_buf = ft_calloc(ft_strlen(line_buf) - i, sizeof(char));
	if (!next_buf)
		return (NULL);
	i++;
	while (line_buf[i] != '\0')
		next_buf[j++] = line_buf[i++];
	next_buf[j] = '\0';
	free(line_buf);
	line_buf = NULL;
	return (next_buf);
}

char	*get_next_line(int fd)
{
	static char	*line_buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!line_buf)
	{
		line_buf = ft_calloc(1, sizeof(char));
		if (!line_buf)
			return (NULL);
	}
	line_buf = read_gnl(fd, line_buf);
	if (!line_buf)
		return (NULL);
	line = push_line(line_buf);
	line_buf = next_line(line_buf);
	if (!line_buf)
	{
		free(line);
		free(line_buf);
		return (NULL);
	}
	return (line);
}

// cat "file"と等価
//   int main()
//   {
//  		int fd;
//  		char *line;
//  		fd = open("./text", O_RDONLY);
//  		while ((line = get_next_line(fd)) != NULL)
//            printf("%s", line);
//  		return (0);
//  	}
