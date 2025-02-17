#include <stdlib.h>

#include "env.h"
extern "C" {
	#include "mlx.h"
}

static void	ft_mlx_free(t_env *env);

void	destroy_env(t_env *env)
{
	ft_mlx_free(env);
	if (env->threads)
		delete[] env->threads;
}

static void	ft_mlx_free(t_env *env)
{
	if (env->img.img)
		mlx_destroy_image(env->mlx, env->img.img);
	if (env->win)
		mlx_destroy_window(env->mlx, env->win);
	if (env->mlx)
		mlx_destroy_display(env->mlx);
	if (env->mlx)
		free(env->mlx);
}
