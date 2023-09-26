/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 19:04:05 by gunjkim           #+#    #+#             */
/*   Updated: 2022/12/13 10:08:41 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putaddr(uintptr_t ptr, int *bytes)
{
	char		*hex;

	hex = "0123456789abcdef";
	if (ptr < 16)
	{
		ft_putstr_pf("0x", bytes);
		if (*bytes == -1)
			return ;
		ft_putchar_pf(hex[ptr], bytes);
		return ;
	}
	ft_putaddr(ptr / 16, bytes);
	if (*bytes == -1)
		return ;
	ft_putchar_pf(hex[ptr % 16], bytes);
}

void	ft_putchar_pf(char c, int *bytes)
{
	if (write(1, &c, 1) == -1)
		*bytes = -1;
	else
		(*bytes)++;
}

void	ft_putstr_pf(char *str, int *bytes)
{
	size_t	len;

	len = 0;
	if (str == NULL)
		str = "(null)";
	while (str[len])
	{
		ft_putchar_pf(str[len], bytes);
		if (*bytes == -1)
			return ;
		len++;
	}
}
