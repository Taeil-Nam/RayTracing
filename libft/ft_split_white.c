/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_white.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:06:49 by gunjkim           #+#    #+#             */
/*   Updated: 2023/03/14 16:40:34 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_white(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static size_t	w_count_white(char const *s)
{
	size_t	flag;
	size_t	wc;

	wc = 0;
	flag = 1;
	while (*s)
	{
		if (!is_white(*s) && flag == 1)
		{
			wc++;
			flag = 0;
		}
		else if (is_white(*s))
			flag = 1;
		s++;
	}
	return (wc);
}

static size_t	ft_strlen_white(char const *s)
{
	size_t	len;

	len = 0;
	while (!is_white(s[len]) && s[len] != '\0')
		len++;
	return (len);
}

void	free_all_white(char **arr, size_t n)
{
	size_t	index;

	index = 0;
	while (index < n)
		free(arr[index++]);
	free(arr);
}

char	**ft_split_white(char const *s)
{
	size_t	wc;
	size_t	index;
	char	**result;

	index = 0;
	wc = w_count_white(s);
	result = (char **)malloc(sizeof(char *) * (wc + 1));
	if (result == NULL)
		return (NULL);
	while (index < wc)
	{
		while (is_white(*s))
			s++;
		result[index] = (char *)malloc(sizeof(char) * (ft_strlen_white(s) + 1));
		if (result[index] == NULL)
		{
			free_all_white(result, index);
			return (NULL);
		}
		ft_strlcpy(result[index++], s, ft_strlen_white(s) + 1);
		s = s + ft_strlen_white(s);
	}
	result[index] = NULL;
	return (result);
}
