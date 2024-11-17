/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:03:22 by tssaito           #+#    #+#             */
/*   Updated: 2024/11/05 14:46:30 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*ans;
	static char	*left[1024];

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	left[fd] = for_gnl_read(fd, left[fd]);
	if (!left[fd] || !*left[fd])
		return (NULL);
	ans = make_ans(left[fd]);
	if (!ans)
		return (NULL);
	left[fd] = make_left(left[fd]);
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
		if (!len && !*tmp)
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

// int main(int argc, char **argv)
//{
//	char *line;
//	int fd1;
//	int fd2;
//
//	(void)argc;
//	fd1 = open(argv[1], O_RDONLY);
//	fd2 = open(argv[2], O_RDONLY);
//	while(1)
//	{
//		line = get_next_line(fd1);
//		if(!line)
//			return (0);
//		printf("fd1: %s", line);
//		line = get_next_line(fd2);
//		if(!line)
//			return (0);
//		printf("fd2: %s", line);
////		printf("succes!\n");
//		free(line);
//	}
//	close(fd1);
//	close(fd2);
//	return (0);
//}
