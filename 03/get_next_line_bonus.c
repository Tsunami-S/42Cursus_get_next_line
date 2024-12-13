/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:58:43 by tssaito           #+#    #+#             */
/*   Updated: 2024/12/13 21:40:47 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	char			c;
	int				check;
	static t_buf	buf[1024];
	t_line			ans;

	ft_init(fd, &ans, &buf[fd]);
	if (fd < 0 || !buf[fd].buf)
		return (NULL);
	while (1)
	{
		c = ft_getchar(fd, &buf[fd]);
		if (c == EOF)
		{
			free(buf[fd].buf);
			break ;
		}
		if (c == READ_ERROR || ans.len == SIZE_MAX)
			return (free(buf[fd].buf), free(ans.line), NULL);
		check = ft_make_ans(c, &ans);
		if (check == MALLOC_ERROR)
			return (free(buf[fd].buf), NULL);
		if (c == '\n')
			break ;
	}
	return (ans.line);
}

# include <fcntl.h>
int	main(int argc, char **argv)
{
	(void)argc;

	char	*line1;
	int		fd1;
	fd1 = open(argv[1], O_RDONLY);
//	char	*line2;
//	int		fd2;
//	fd2 = open(argv[2], O_RDONLY);
	while (1)
	{
		line1 = get_next_line(fd1);
		if (!line1)
			break;
		printf("line1: %s", line1);
		free(line1);
//		line2 = get_next_line(fd2);
//		if (!line2)
//			break;
//		printf("line2: %s", line2);
//		free(line2);
		printf("=================\n");
	}
	close(fd1);
//	close(fd2);
	return (0);
}
