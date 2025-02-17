/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 22:07:37 by ibertran          #+#    #+#             */
/*   Updated: 2024/10/01 21:31:51 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

#include <X11/Xlib.h>
extern "C" {
	#include "mlx.h"
}
#include "mlx_int.h"
#include "env.h"
#include "ft_time.h"

int	init_env(t_env *env)
{
	env->mlx = mlx_init();
	if (NULL == env->mlx)
	{
		dprintf(STDERR_FILENO, MLX_ERR2, FATAL);
		return (1);
	}
	env->nb_threads = get_nprocs();
	env->threads = new std::thread[env->nb_threads];
	if (!env->threads)
	{
		dprintf(STDERR_FILENO, MLX_ERR2, FATAL);
		return (1);
	}
	env->mlx_info.res = (t_v2d_i){WIDTH, HEIGHT};
	env->camera_zoom = 1.0;
	env->camera_pos = (t_v2d_d){0, 0};
	env->flags = 0;
	init_timer(&env->frame_timer, 0, MANUAL_RESET);
	for (int i = 0; i < PERLIN_NOISE; i++) {
		env->perlin[i] = PerlinNoise(rand());
	}
	return (0);
}
