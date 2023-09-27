/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:29:33 by tnam              #+#    #+#             */
/*   Updated: 2023/09/27 12:29:35 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_BONUS_H
# define MLX_UTILS_BONUS_H

# include "mlx.h"

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

int		exit_hook(void);
int		key_hook(int keycode, t_vars *vars);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif