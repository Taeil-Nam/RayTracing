/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:32:36 by tnam              #+#    #+#             */
/*   Updated: 2023/09/27 12:32:37 by tnam             ###   ########.fr       */
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
