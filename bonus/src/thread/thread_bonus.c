#include "minirt_bonus.h"

void	multi_threading(t_thread *threads, t_minirt *minirt)
{
	int	i;

	i = 0;
	while (i < THREAD_NUM)
	{
		if (minirt->illumination == PATH)
			pthread_create(&threads[i].thread, NULL, path_trace, &threads[i]);
		else
			pthread_create(&threads[i].thread, NULL, phong_trace, &threads[i]);
		i++;
	}
	i = 0;
	while (i < THREAD_NUM)
	{
		pthread_join(threads[i].thread, NULL);
		i++;
	}
}
