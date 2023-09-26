/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:11:51 by gunjkim           #+#    #+#             */
/*   Updated: 2022/11/21 13:37:06 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	d_count(int n)
{
	size_t	dc;

	dc = 0;
	if (n <= 0)
		dc++;
	while (n != 0)
	{
		dc++;
		n = n / 10;
	}
	return (dc);
}

char	*ft_itoa(int n)
{
	size_t		dc;
	char		*result;
	long long	n_tmp;	

	dc = d_count(n);
	n_tmp = (long long)n;
	if (n_tmp < 0)
		n_tmp = n_tmp * -1;
	result = malloc(sizeof(char) * (dc + 1));
	if (result == NULL)
		return (NULL);
	if (n < 0)
		result[0] = '-';
	result[dc--] = '\0';
	while (n_tmp > 9)
	{
		result[dc--] = n_tmp % 10 + '0';
		n_tmp = n_tmp / 10;
	}
	result[dc] = n_tmp + '0';
	return (result);
}
