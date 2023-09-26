/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:22:16 by gunjkim           #+#    #+#             */
/*   Updated: 2023/08/25 15:42:07 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*ft_isspace(const char *str)
{
	while ((9 <= *str && *str <= 13) || *str == 32)
		str++;
	return (str);
}

int	ft_atoi(const char *str)
{
	int			sign;
	long long	result;

	sign = 1;
	result = 0;
	str = ft_isspace(str);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
		if (*str == '\0' || *str == '+' || *str == '-')
			return (-1);
	}
	while (*str)
	{
		if ('0' <= *str && *str <= '9')
			result = result * 10 + (*str - '0');
		else
			return (-1);
		if (result * sign < INT32_MIN || result * sign > INT32_MAX)
			return (-1);
		str++;
	}
	return (result * sign);
}
