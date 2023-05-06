/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syoma.k <syoma.k@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:45:21 by syoma.k           #+#    #+#             */
/*   Updated: 2023/05/06 21:21:27 by syoma.k          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
/*
【注意】
・callocを使っているのでバッファサイズが大きい時に時間がかかる
・ファイル終端の読み込みが終わったら空の文字列を返すようにしている。
→そのため、42のgnl課題では以下を変更する必要あり。
	char	*get_next_line(int fd)関数内の↓のreturnを""からNULLを変える必要あり
		if (line_buf[0] == '\0')
			return ("");
*/


/*2回目以降のgnlの呼び出し時に、
line_bufにはmallocで確保された文字列 or 空の文字列""
が入る。前者は動的領域で、後者は静的領域のためフリーする条件を入れている*/
char	*join_free(char *line_buf, char *buffer)
{
	char	*reline_buf;

	reline_buf = ft_strjoin(line_buf, buffer);
	if (line_buf[0] != '\0')
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

/*ファイルの読み込みが全て終了して、next_line関数が返す文字列がなくなった時からの文字列を返す*/
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
		return ("");
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

/*
 ・改行を含めない1行を返す
 ・mallocなどのエラーが出ればNULLを返す
 ・ファイルの終端に達した後に呼び出した場合、空の文字列""を返す

 [2回目以降の呼び出し時line_buf]
 ・改行以降の文字列を	動的な領域	で保持
 or
 ・空の文字列を	静的な領域	で保持
*/
char	*get_next_line(int fd)
{
	static char	*line_buf[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!line_buf[fd])
		line_buf[fd] = "";
	line_buf[fd] = read_gnl(fd, line_buf[fd]);
	if (!line_buf[fd])
		return (NULL);
	if (line_buf[fd][0] == '\0')
		return ("");
	line = push_line(line_buf[fd]);
	line_buf[fd] = next_line(line_buf[fd]);
	if (!line_buf[fd])
	{
		free(line);
		free(line_buf[fd]);
		return (NULL);
	}
	return (line);
}

//   int main()
//   {
//  		int fd;
//  		char *line;
//  		fd = open("./text", O_RDONLY);
//  		while ((line = get_next_line(fd))> 0)
//            printf("%s", line);
//  		return (0);
//  	}
