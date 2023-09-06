#ifndef MATERIAL_H
# define MATERIAL_H

# include "minirt.h"
# include "texture.h"

typedef t_color	(*t_emit)(t_hit_rec *, t_point3 *, t_texture *);
typedef bool	(*t_scatter)(t_ray *, t_hit_rec *, t_color *, t_ray *);

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
	double			ir;
	t_texture		t;
	t_emit			emit;
	t_scatter		scatter;
}	t_material;

bool	scatter_diffuse(t_ray *r, t_hit_rec *rec, t_color *att, t_ray *scat);
bool	scatter_light(t_ray *r, t_hit_rec *rec, t_color *att, t_ray *scat);
bool	scatter_metal(t_ray *r, t_hit_rec *rec, t_color *att, t_ray *scat);
bool	scatter_dielectric(t_ray *r, t_hit_rec *rec, t_color *att, t_ray *scat);
t_color	emit_general(t_hit_rec *rec, t_point3 *p, t_texture *t);
t_color	emit_light(t_hit_rec *rec, t_point3 *p, t_texture *t);
#endif
