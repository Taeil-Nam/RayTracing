#ifndef MLX_UTILS_H
# define MLX_UTILS_H

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
void	minirt_init(t_data *image, t_vars *vars);

#endif