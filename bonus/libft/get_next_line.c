/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:57:04 by gunjkim           #+#    #+#             */
/*   Updated: 2023/01/25 12:59:55 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*expand_line(t_buff *b, char *s)
{
	char	*line;
	size_t	added;

	if (ft_strchr(b->buff + b->offset, '\n') != NULL)
		b->total_len += get_strlen_c(b->buff + b->offset, '\n') + 1;
	else
		b->total_len += get_strlen_c(b->buff + b->offset, '\0');
	line = (char *)malloc(sizeof(char) * (b->total_len + 1));
	if (line == NULL)
	{
		free(s);
		return (NULL);
	}
	ft_strlcpy(line, s, b->total_len + 1);
	ft_strlcat(line, b->buff + b->offset, b->total_len + 1);
	added = b->total_len - get_strlen_c(s, '\0');
	b->offset += added;
	if (b->offset == (size_t)b->nbytes)
		b->offset = 0;
	free(s);
	return (line);
}

static char	*make_next_line(int fd, t_buff *b)
{
	char	*line;

	line = ft_strdup("");
	if (line == NULL)
		return (NULL);
	while (ft_strchr(line, '\n') == NULL)
	{
		if (b->offset == 0)
		{
			b->nbytes = read(fd, b->buff, BUFFER_SIZE);
			if (get_strlen_c(line, '\0') > 0 && b->nbytes == 0)
				return (line);
			if (b->nbytes <= 0)
			{
				b->offset = 0;
				free(line);
				return (NULL);
			}
			b->buff[b->nbytes] = '\0';
		}
		line = expand_line(b, line);
		if (line == NULL)
			return (NULL);
	}
	return (line);
}

static t_buff	*find_insert(t_buff *buff_arr, int fd)
{
	int	i;

	i = 1;
	while (i < OPEN_MAX)
	{
		if (buff_arr[i].fd == fd)
			return (&buff_arr[i]);
		if (buff_arr[i].fd == 0)
			break ;
		if (i == OPEN_MAX - 1)
			return (NULL);
		i++;
	}
	buff_arr[i].fd = fd;
	return (&buff_arr[i]);
}

char	*get_next_line(int fd)
{
	static t_buff	buff_arr[OPEN_MAX];
	char			*new_line;
	t_buff			*fd_buffer;

	fd_buffer = NULL;
	if (fd < 0)
		return (NULL);
	if (fd != 0)
	{
		fd_buffer = find_insert(buff_arr, fd);
		if (fd_buffer == NULL)
			return (NULL);
	}
	else if (fd == 0)
		fd_buffer = &buff_arr[0];
	fd_buffer->total_len = 0;
	new_line = make_next_line(fd, fd_buffer);
	return (new_line);
}
