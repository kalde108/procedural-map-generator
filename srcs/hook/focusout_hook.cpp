/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   focusout_hook.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:05:53 by ibertran          #+#    #+#             */
/*   Updated: 2025/02/05 15:27:59 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

extern "C"
{
	#include "mlx.h"
}

#include "env.h"

int	focusout_hook(t_env *env)
{
	int	i;

	i = 0;
	while (i < KEY_COUNT)
	{
		env->input.key_state[i] = KEY_STATE_IDLE;
		i++;
	}
	env->input.mouse.status = false;
	mlx_mouse_show(env->mlx, env->win);
	return (0);
}
