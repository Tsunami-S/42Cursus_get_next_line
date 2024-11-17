/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:03:28 by tssaito           #+#    #+#             */
/*   Updated: 2024/11/05 12:42:09 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count])
		count++;
	return (count);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == 0)
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	int		count;
	int		i;
	char	*ans;

	count = ft_strlen(s);
	ans = (char *)malloc(sizeof(char) * count + 1);
	if (ans == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ans[i] = s[i];
		i++;
	}
	ans[i] = '\0';
	return (ans);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ans;
	size_t	max_size;

	max_size = (size_t)(-1);
	if (size && nmemb > max_size / size)
		return (NULL);
	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	ans = malloc(nmemb * size);
	if (ans == NULL)
		return (NULL);
	ft_memset(ans, 0, nmemb * size);
	return (ans);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*_s;

	_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		_s[i] = c;
		i++;
	}
	return (s);
}
