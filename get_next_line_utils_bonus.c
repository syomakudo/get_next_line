/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syoma.k <syoma.k@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:35:43 by syoma.k           #+#    #+#             */
/*   Updated: 2023/03/15 21:33:42 by syoma.k          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_bzero(void *b, size_t len)
{
	if (len > INT32_MAX / 100)
		len = INT32_MAX / 1000;
	while (len-- > 0)
	{
		*(char *)b = 0;
		b++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	check;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	check = count * size;
	if (check / count != size)
		return (NULL);
	p = (void *)malloc(count * size);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, count * size);
	return (p);
}

int	ft_strchr(const char *string, int c)
{
	while ((*string) != '\0')
	{
		if (*((char *)(string++)) == (char)c)
			return (1);
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	j;
	char	*result;

	if (!s1 | !s2)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (result == NULL)
		return (NULL);
	len = 0;
	j = 0;
	while (s1[j])
		result[len++] = s1[j++];
	j = 0;
	while (s2[j])
		result[len++] = s2[j++];
	result[len] = '\0';
	return (result);
}
