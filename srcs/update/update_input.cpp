#include "env.h"
extern "C" {
	#include "mlx.h"
}

void update_input(t_env *env)
{
	for (int i = 0; i < KEY_COUNT; i++)
	{
		if (env->input.key_pressed[i])
		{
			if (env->input.key_state[i] == KEY_STATE_IDLE || env->input.key_state[i] == KEY_STATE_RELEASED)
				env->input.key_state[i] = KEY_STATE_PRESSED;
			else
				env->input.key_state[i] = KEY_STATE_HELD;
		}
		else
		{
			if (env->input.key_state[i] == KEY_STATE_HELD || env->input.key_state[i] == KEY_STATE_PRESSED)
				env->input.key_state[i] = KEY_STATE_RELEASED;
			else
				env->input.key_state[i] = KEY_STATE_IDLE;
		}
	}
	t_v2d_i mouse_pos;
	mlx_mouse_get_pos(env->mlx, env->win, &mouse_pos.x, &mouse_pos.y);
	env->input.mouse.delta = (t_v2d_i){mouse_pos.x - env->input.mouse.x, mouse_pos.y - env->input.mouse.y};
	env->input.mouse.x = mouse_pos.x;
	env->input.mouse.y = mouse_pos.y;
}
