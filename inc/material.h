#ifndef MATERIAL_H
# define MATERIAL_H

# include "bvh.h"
# include "texture.h"
# include "stdbool.h"

enum e_mat_type
{
	diffuse,
	metal,
	light,
};

typedef struct s_material
{
	enum e_mat_type	mat_type;
	double			fuzz;
	int				ir;
	t_texture		*t;
	t_color			(*emit)(double, double, t_point3 *, t_texture *);
	bool			(*scatter)(t_ray *, t_hit_record *, t_color *, t_ray *);
}	t_material;

bool	scatter_diffuse(t_ray *r, t_hit_record *rec, t_color *att, t_ray *scat);
bool	scatter_light(t_ray *r, t_hit_record *rec, t_color *att, t_ray *scat);
t_color	emit_general(double u, double v, t_point3 *p, t_texture *t);
t_color	emit_light(double u, double v, t_point3 *p, t_texture *t);
#endif
