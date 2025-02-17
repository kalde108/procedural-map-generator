/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyup_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:53:11 by ibertran          #+#    #+#             */
/*   Updated: 2024/10/26 19:03:38 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "key_index.h"

# include <stdio.h>

int	keyup_hook(int keycode, t_env *env)
{
	int	keyindex;

	env->input.keyboard_used = false;
	keyindex = get_keyindex(keycode);
	if (keyindex != -1)
	{
		env->input.keyboard_used = true;
		env->input.key_pressed[keyindex] = 0;
		// if (env->input.key_state[keyindex] == KEY_STATE_HELD)
		// 	env->input.key_state[keyindex] = KEY_STATE_RELEASED;
		// else
		// 	env->input.key_state[keyindex] = KEY_STATE_IDLE;
		// printf("state up=%d\n", env->input.key_state[keyindex]);
	}
	return (0);
}
