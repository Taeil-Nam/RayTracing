/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:32:26 by tnam              #+#    #+#             */
/*   Updated: 2023/09/27 12:32:27 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	minirt_error_exit(void)
{
	perror("Error\nminiRT");
	exit(1);
}

void	minirt_str_error_exit(char *str)
{
	errno = 0;
	perror(str);
	exit(1);
}
