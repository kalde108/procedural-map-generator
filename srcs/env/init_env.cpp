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

# include <iostream>

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
	env->rng = Random(rand());
	// env->perlin[NOISE_CONTINENTS] = MinecraftNoise(rand(), -9, std::vector<double>({1.0, 1.0, 2.0, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0}));
	// env->perlin[NOISE_EROSION] = MinecraftNoise(rand(), -6, std::vector<double>({1.0, 0.0, 1.0}));
	env->noise[NOISE_CONTINENTS] = MultiOctaveNoise(&env->rng, -9, std::vector<double>({1.0, 1.0, 2.0, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0}));
	std::cout << "max continentalness value: " << env->noise[NOISE_CONTINENTS].maxValue << std::endl;
	env->rng.consume(100);
	env->noise[NOISE_EROSION] = MultiOctaveNoise(&env->rng, -9, std::vector<double>({1.0, 1.0, 0.0, 1.0, 1.0}));
	std::cout << "max erosion value: " << env->noise[NOISE_EROSION].maxValue << std::endl;
	env->rng.consume(100);
	env->noise[NOISE_TEMPERATURE] = MultiOctaveNoise(&env->rng, -10, std::vector<double>({1.5, 0.0, 1.0, 0.0, 0.0, 0.0}));
	std::cout << "max temperature value: " << env->noise[NOISE_TEMPERATURE].maxValue << std::endl;
	env->rng.consume(100);
	env->noise[NOISE_VEGETATION] = MultiOctaveNoise(&env->rng, -8, std::vector<double>({1.0, 1.0, 0.0, 0.0, 0.0, 0.0}));
	std::cout << "max vegetation value: " << env->noise[NOISE_VEGETATION].maxValue << std::endl;
	env->rng.consume(100);
	env->noise[NOISE_RIDGES] = MultiOctaveNoise(&env->rng, -7, std::vector<double>({1.0, 2.0, 1.0, 0.0, 0.0, 0.0}));
	std::cout << "max weirdness value: " << env->noise[NOISE_RIDGES].maxValue << std::endl;
	return (0);
}
