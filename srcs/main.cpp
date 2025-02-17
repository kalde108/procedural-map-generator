#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "env.h"
extern "C" {
	#include "mlx.h"
}

int main(int argc, char **argv)
{
	t_env	env;

	memset(&env, 0, sizeof(t_env));
	if (check_arguments(argc, argv))
		return (1);
	srand(time(NULL));
	if (init_env(&env))
	{
		destroy_env(&env);
		return (1);
	}
	if (open_mlx_window(&env))
	{
		destroy_env(&env);
		return (1);
	}
	mlx_mouse_get_pos(env.mlx, env.win, &env.input.mouse.x, &env.input.mouse.y);
	mlx_loop(env.mlx);
	
	destroy_env(&env);
	return (0);
}
