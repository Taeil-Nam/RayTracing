#include "minirt.h"

void	multi_threading(t_thread *threads, t_minirt *minirt)
{
	int	i;
	int	ret;

	i = 0;
	while (i < THREAD_NUM)
	{
		if (minirt->illumination == PATH)
			ret = pthread_create(&threads[i].thread,
					NULL, path_trace, &threads[i]);
		else
			ret = pthread_create(&threads[i].thread,
					NULL, phong_trace, &threads[i]);
		if (ret != 0)
			minirt_str_error_exit("Error\nminiRT: thread create");
		i++;
	}
	i = 0;
	while (i < THREAD_NUM)
	{
		if (pthread_join(threads[i].thread, NULL) != 0)
			minirt_str_error_exit("Error\nminiRT: thread join");
		i++;
	}
}
