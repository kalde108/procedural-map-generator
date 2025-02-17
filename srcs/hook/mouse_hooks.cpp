/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:47:54 by kchillon          #+#    #+#             */
/*   Updated: 2025/02/05 15:17:26 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <X11/Xutil.h>

#include "env.h"
extern "C" {
	#include "mlx.h"
}

static void	left_button(void *mlx, void *win, t_mouse *mouse)
{
	(void)mlx;
	(void)win;
	if (mouse->status & MOUSE_BUTTON_LEFT)
		mouse->status &= ~MOUSE_BUTTON_LEFT;
	else
		mouse->status |= MOUSE_BUTTON_LEFT;
	mouse->delta.x = 0;
}

static void	right_button(int x, int y, t_mouse *mouse)
{
	if (mouse->status & MOUSE_BUTTON_RIGHT)
		mouse->status &= ~MOUSE_BUTTON_RIGHT;
	else
		mouse->status |= MOUSE_BUTTON_RIGHT;
	mouse->x = x;
	mouse->y = y;
	mouse->delta = (t_v2d_i){0, 0};
}

int	buttonpress_hook(int button, int x, int y, t_env *env)
{
	(void)button;
	(void)x;
	(void)y;
	(void)env;
	if (Button1 == button)
		left_button(env->mlx, env->win, &env->input.mouse);
	if (Button3 == button)
		right_button(x, y, &env->input.mouse);
	if (Button4 == button)
	{
		env->camera_zoom *= 1.1;
	}
		// env->input.mouse.status |= MOUSE_WHEEL_UP;
	if (Button5 == button)
	{
		env->camera_zoom *= 0.9;
		// env->camera_zoom -= 1;
		if (env->camera_zoom <= 0.1)
			env->camera_zoom = 0.1;
	}
		// env->input.mouse.status |= MOUSE_WHEEL_DOWN;
	return (0);
}

int	buttonrelease_hook(int button, int x, int y, t_env *env)
{
	(void)button;
	(void)x;
	(void)y;
	(void)env;
	if (Button3 == button && env->input.mouse.status & MOUSE_BUTTON_RIGHT)
		env->input.mouse.status &= ~MOUSE_BUTTON_RIGHT;
	// if (Button4 == button)
	// 	env->input.mouse.status &= ~MOUSE_WHEEL_UP;
	// if (Button5 == button)
	// 	env->input.mouse.status &= ~MOUSE_WHEEL_DOWN;
	return (0);
}
