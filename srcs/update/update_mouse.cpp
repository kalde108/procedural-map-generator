extern "C" {
	#include "mlx.h"
}
#include "env.h"

#include <stdio.h>

void	update_mouse(t_env *env)
{
	if (!(env->input.mouse.status & MOUSE_BUTTON_RIGHT))
	{
		return ;
	}
	printf("UPDATE MOUSE\n");

	int x;
	int y;
	mlx_mouse_get_pos(env->mlx, env->win, &x, &y);
	env->input.mouse.delta.x = x - env->input.mouse.x;
	env->input.mouse.delta.y = y - env->input.mouse.y;
	env->input.mouse.x = x;
	env->input.mouse.y = y;
}
