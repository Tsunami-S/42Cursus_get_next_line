/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:03:06 by tssaito           #+#    #+#             */
/*   Updated: 2024/11/05 15:51:28 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*ans;
	static char	*left;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	left = for_gnl_read(fd, left);
	if (!left || !*left)
		return (NULL);
	ans = make_ans(left);
	if (!ans)
		return (NULL);
	left = make_left(left);
	return (ans);
}

char	*for_gnl_read(int fd, char *left)
{
	char	*tmp;
	int		len;
	int		flag;

	tmp = (char *)calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	flag = 1;
	while (flag)
	{
		len = read(fd, tmp, BUFFER_SIZE);
		if (len < 0)
			return (free(tmp), NULL);
		if (!len)
			break ;
		tmp[len] = '\0';
		if (ft_strchr(tmp, '\n'))
			flag = 0;
		if (!left)
			left = ft_strdup(tmp);
		else
			left = for_gnl_strjoin(left, tmp);
	}
	return (free(tmp), left);
}

char	*make_ans(char *left)
{
	int		len;
	int		i;
	char	*ans;

	len = 0;
	while (left[len] && left[len] != '\n')
		len++;
	ans = (char *)malloc(sizeof(char) * len + 2);
	if (!ans)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ans[i] = left[i];
		i++;
	}
	if (left[i] == '\n')
	{
		ans[i] = '\n';
		i++;
	}
	ans[i] = '\0';
	return (ans);
}

char	*make_left(char *left)
{
	char	*ans;
	char	*tmp;

	tmp = left;
	while (*left && *left != '\n')
		left++;
	if (!*left)
	{
		free(tmp);
		return (NULL);
	}
	if (*left == '\n')
		left++;
	ans = ft_strdup(left);
	free(tmp);
	return (ans);
}

char	*for_gnl_strjoin(char *s1, char const *s2)
{
	char	*ans;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	ans = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ans)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		ans[i++] = s1[j++];
	j = 0;
	while (s2[j])
		ans[i++] = s2[j++];
	ans[i] = '\0';
	free(s1);
	return (ans);
}

//int	main(int argc, char **argv)
//{
//	char	*line;
//	int		fd;
//
//	(void)argc;
//	fd = open(argv[1], O_RDONLY);
//	while (1)
//	{
//		line = get_next_line(fd);
//		if (!line)
//			return (0);
//		printf("line: %s", line);
//		free(line);
//	}
//	close(fd);
//	return (0);
//}
