/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:57:09 by gunjkim           #+#    #+#             */
/*   Updated: 2023/01/25 12:59:54 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include "libft.h"

typedef struct s_buff
{
	int		fd;
	char	buff[BUFFER_SIZE + 1];
	ssize_t	nbytes;
	size_t	offset;
	size_t	total_len;
}	t_buff;

char	*get_next_line(int fd);

size_t	get_strlen_c(const char *s, const char c);

#endif
