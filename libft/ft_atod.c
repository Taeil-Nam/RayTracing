#include "libft.h"

int	check_format(char *str, int *atod_err)
{
	int	cnt;
	int	is_valid;

	cnt = 0;
	is_valid = 1;
	if (*str == '.')
		is_valid = 0;
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != '.')
			is_valid = 0;
		if (*str == '.')
			cnt++;
		str++;
	}
	if (cnt <= 1 && is_valid == 1)
		return (1);
	*atod_err = ATOD_FORMAT_ERR;
	return (0);
}

double	ten_nth_sq(int n)
{
	int		i;
	double	ret;

	i = 0;
	ret = 1;
	while (i < n)
	{
		ret = 10 * ret;
		i++;
	}
	return (ret);
}

int	check_sign(char *str, int *sign)
{
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
		{
			*sign = -1;
			return (1);
		}
		*sign = 1;
		return (1);
	}
	*sign = 1;
	return (0);
}

double	ft_atod(char *str, int *atod_err)
{
	double	ret;
	int		sign;
	int		i;

	ret = 0;
	i = 1;
	if (check_sign(str, &sign) != 0)
		str++;
	if (!check_format(str, atod_err))
		return (ret);
	while (*str && *str != '.')
	{
		ret = 10 * ret + (*str - '0');
		str++;
	}
	if (*str == '.')
		str++;
	while (*str)
	{
		ret = ret + (*str - '0') / ten_nth_sq(i++);
		str++;
	}
	return (ret * sign);
}
