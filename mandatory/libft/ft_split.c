/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:06:49 by gunjkim           #+#    #+#             */
/*   Updated: 2023/03/14 16:38:37 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	w_count(char const *s, char c)
{
	size_t	flag;
	size_t	wc;

	wc = 0;
	flag = 1;
	while (*s)
	{
		if (*s != c && flag == 1)
		{
			wc++;
			flag = 0;
		}
		else if (*s == c)
			flag = 1;
		s++;
	}
	return (wc);
}

static size_t	ft_strlen_c(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] != c && s[len] != '\0')
		len++;
	return (len);
}

void	free_all(char **arr, size_t n)
{
	size_t	index;

	index = 0;
	while (index < n)
		free(arr[index++]);
	free(arr);
}

char	**ft_split(char const *s, char c)
{
	size_t	wc;
	size_t	index;
	char	**result;

	index = 0;
	wc = w_count(s, c);
	result = (char **)malloc(sizeof(char *) * (wc + 1));
	if (result == NULL)
		return (NULL);
	while (index < wc)
	{
		while (*s == c)
			s++;
		result[index] = (char *)malloc(sizeof(char) * (ft_strlen_c(s, c) + 1));
		if (result[index] == NULL)
		{
			free_all(result, index);
			return (NULL);
		}
		ft_strlcpy(result[index++], s, ft_strlen_c(s, c) + 1);
		s = s + ft_strlen_c(s, c);
	}
	result[index] = NULL;
	return (result);
}
