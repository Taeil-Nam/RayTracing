/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:11:40 by gunjkim           #+#    #+#             */
/*   Updated: 2022/12/13 10:08:17 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	base_rec(unsigned int nbr, int *bytes, unsigned int b_len, char *base)
{
	if (nbr < b_len)
	{
		if (write(1, &base[nbr], 1) == -1)
			*bytes = -1;
		else
			(*bytes)++;
	}
	else
	{
		base_rec(nbr / b_len, bytes, b_len, base);
		if (*bytes == -1)
			return ;
		if (write(1, &base[nbr % b_len], 1) == -1)
			*bytes = -1;
		else
			(*bytes)++;
	}
}

void	ft_puthex_lower(unsigned int nbr, int *bytes)
{
	base_rec(nbr, bytes, 16, "0123456789abcdef");
}

void	ft_puthex_upper(unsigned int nbr, int *bytes)
{
	base_rec(nbr, bytes, 16, "0123456789ABCDEF");
}

void	ft_putunbr(unsigned int nbr, int *bytes)
{
	base_rec(nbr, bytes, 10, "0123456789");
}

void	ft_putnbr_pf(int nbr, int *bytes)
{
	if (nbr == -2147483648)
	{
		ft_putstr_pf("-2147483648", bytes);
		return ;
	}
	if (nbr < 0)
	{
		ft_putchar_pf('-', bytes);
		if (*bytes == -1)
			return ;
		nbr = nbr * -1;
	}
	base_rec(nbr, bytes, 10, "0123456789");
}
