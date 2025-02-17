/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_mlx_window.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:51:17 by ibertran          #+#    #+#             */
/*   Updated: 2025/02/05 15:22:02 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <X11/Xutil.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>

extern "C" {
	#include "mlx.h"
}
#include "mlx_tools.h"
#include "env.h"

#include <string>

static void	setup_mlx_hooks(t_env *env);

int	open_mlx_window(t_env *env)
{
	std::string win_name(WIN_NAME);
	env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, (char *)win_name.c_str());
	if (!env->win)
	{
		dprintf(STDERR_FILENO, MLX_ERR2, FATAL);
		return (1);
	}
	env->img.img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	if (!env->img.img)
	{
		dprintf(STDERR_FILENO, MLX_ERR2, FATAL);
		return (1);
	}
	env->img.addr = (t_color *)mlx_get_data_addr(env->img.img,
			&env->img.bits_per_pixel,
			&env->img.line_length,
			&env->img.endian);
	if (!env->img.addr)
	{
		dprintf(STDERR_FILENO, MLX_ERR2, FATAL);
		return (1);
	}
	setup_mlx_hooks(env);
	return (0);
}

static void	setup_mlx_hooks(t_env *env)
{
	mlx_hook(env->win,
		DestroyNotify, StructureNotifyMask, reinterpret_cast<int (*)()>(mlx_loop_end), env->mlx);
	mlx_hook(env->win,
		KeyPress, KeyPressMask, reinterpret_cast<int (*)()>(keydown_hook), env);
	mlx_hook(env->win,
		KeyRelease, KeyReleaseMask, reinterpret_cast<int (*)()>(keyup_hook), env);
	mlx_hook(env->win,
		ButtonPress, ButtonPressMask, reinterpret_cast<int (*)()>(buttonpress_hook), env);
	mlx_hook(env->win,
		ButtonRelease, ButtonReleaseMask, reinterpret_cast<int (*)()>(buttonrelease_hook), env);
	mlx_loop_hook(env->mlx, reinterpret_cast<int (*)()>(render), env);
}
