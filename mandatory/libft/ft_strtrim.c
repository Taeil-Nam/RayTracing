/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 19:18:48 by gunjkim           #+#    #+#             */
/*   Updated: 2022/11/17 17:20:20 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	begin;
	size_t	end;
	size_t	index;
	char	*str_trim;

	begin = 0;
	end = 0;
	index = 0;
	while (ft_strchr(set, s1[begin]) && s1[begin])
		begin++;
	while (s1[index])
	{
		if (ft_strchr(set, s1[index]) == NULL)
			end = index;
		index++;
	}
	if (begin == ft_strlen(s1))
		return (ft_strdup(""));
	str_trim = (char *)malloc(sizeof(char) * (end - begin + 2));
	if (str_trim == NULL)
		return (NULL);
	ft_strlcpy(str_trim, s1 + begin, end - begin + 2);
	return (str_trim);
}
