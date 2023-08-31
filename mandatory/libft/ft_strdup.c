/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:17:32 by gunjkim           #+#    #+#             */
/*   Updated: 2022/11/16 18:35:09 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len_with_null;
	size_t	index;
	char	*copy;

	index = 0;
	len_with_null = ft_strlen(s1) + 1;
	copy = (char *)malloc(sizeof(char) * len_with_null);
	if (copy == NULL)
		return (NULL);
	while (s1[index])
	{
		copy[index] = s1[index];
		index++;
	}
	copy[index] = '\0';
	return (copy);
}
