/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:42:47 by gunjkim           #+#    #+#             */
/*   Updated: 2022/11/18 18:31:31 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	index;
	size_t	s_len;
	char	*last_loc;
	char	c_tmp;

	index = 0;
	s_len = ft_strlen(s);
	c_tmp = (char)c;
	last_loc = NULL;
	while (index <= s_len)
	{
		if (s[index] == c_tmp)
			last_loc = (char *)(&(s[index]));
		index++;
	}
	return (last_loc);
}
