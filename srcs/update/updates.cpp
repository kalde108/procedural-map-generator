# include <stdio.h>

extern "C" {
	#include "mlx.h"
}
#include "update.h"
#include "key_index.h"

void update_camera(t_env *env)
{
	if (env->input.mouse.status & MOUSE_BUTTON_RIGHT)
	{
		env->camera_pos.x -= (float)env->input.mouse.delta.x * ((float)1 / HEIGHT) * env->camera_zoom;
		env->camera_pos.y -= (float)env->input.mouse.delta.y * ((float)1 / HEIGHT) * env->camera_zoom;
		// printf("camera_pos: %f %f\n", env->camera_pos.x, env->camera_pos.y);
	}
	if (env->input.key_state[KEY_Z] == KEY_STATE_PRESSED)
	{
		env->flags = ++env->flags % NOISE_COUNT;
	}
	if (env->input.key_state[KEY_R] == KEY_STATE_PRESSED)
	{
		env->pv = ++env->pv % 2;
	}
}

void	updates(t_env *env)
{
	update_input(env);
	update_camera(env);
}
