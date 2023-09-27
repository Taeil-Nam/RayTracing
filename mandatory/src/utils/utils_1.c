/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:30:47 by gunjkim           #+#    #+#             */
/*   Updated: 2023/09/27 12:30:59 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

unsigned int	custom_rand(void)
{
	static unsigned long	seed = 1UL;
	const unsigned long		a = 1103515245UL;
	const unsigned long		c = 12345UL;
	const unsigned long		m = 1UL << 31;

	seed = (a * seed + c) % m;
	return (seed);
}

double	random_double(void)
{
	return (custom_rand() / (2147483647 + 1.0));
}

double	random_double_mm(double min, double max)
{
	return (min + ((max - min) * random_double()));
}

int	random_int(void)
{
	return ((int)random_double());
}

int	random_int_mm(int min, int max)
{
	return ((int)random_double_mm(min, max + 1));
}
