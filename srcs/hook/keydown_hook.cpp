/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keydown_hook.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:52:47 by ibertran          #+#    #+#             */
/*   Updated: 2025/02/05 15:17:26 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <X11/Xutil.h>

#include "env.h"
#include "key_index.h"
extern "C" {
	#include "mlx.h"
}

int	keydown_hook(int keycode, t_env *env)
{
	int	keyindex;

	env->input.keyboard_used = false;
	if (keycode == XK_Escape)
		mlx_loop_end(env->mlx);
	keyindex = get_keyindex(keycode);
	if (keyindex != -1)
	{
		env->input.keyboard_used = true;
		env->input.key_pressed[keyindex] = 1;
		// if (env->input.key_state[keyindex] == KEY_STATE_IDLE)
		// 	env->input.key_state[keyindex] = KEY_STATE_PRESSED;
		// else
		// 	env->input.key_state[keyindex] = KEY_STATE_HELD;
		// printf("state down=%d\n", env->input.key_state[keyindex]);
	}
	printf("keycode=%d\n", keycode);
	return (0);
}
