#ifndef VEC3_H
# define VEC3_H

# include <math.h>
# include <stdbool.h>

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef t_vec3	t_point3;
typedef t_vec3	t_color;

/* vec3_1.c */
t_vec3	vec3_add(t_vec3 left, t_vec3 right); //left + right의 대한 값 반환
t_vec3	vec3_sub(t_vec3 left, t_vec3 right); //left - right의 대한 값 반환
t_vec3	vec3_mul_vec3(t_vec3 left, t_vec3 right); //left * right의 대한 값 반환
t_vec3	vec3_mul_scalar(t_vec3 left, double right); //left * scalar의 대한 값 반환

/* vec3_2.c */
double	vec3_length(t_vec3 v); //벡터의 길이 구하는 함수
double	vec3_squared(t_vec3 v); //벡터 거리 제곱
double	vec3_dot(t_vec3 left, t_vec3 right); // dot product
t_vec3	vec3_cross(t_vec3 left, t_vec3 right); // cross product
t_vec3	vec3_unit(t_vec3 v); //make unit vector from v

/* vec3_3.c */
t_vec3	vec3_random(void); //random vec3
t_vec3	vec3_random_mm(double min, double max); //random vec3 with min max
t_vec3	vec3_random_in_unit_sphere(void); //return vector in unitsphere
t_vec3	vec3_random_unit(void); //return random unit vector

/* vec3_4.c */
bool	vec3_near_zero(t_vec3 v); //vec3가 0vector인지
void	vec3_print(t_vec3 v); //print vec3
t_vec3	vec3_reflect(t_vec3 v, t_vec3 n); //return reflect vector
t_vec3	vec3_refract(t_vec3 uv, t_vec3 n, double etai_over_etat);

/* vec3_5.c */
void	vec3_init(t_vec3 *v, double x, double y, double z);
t_vec3	vec3_instant(double x, double y, double z);

#endif
