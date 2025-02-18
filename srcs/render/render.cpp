#include <stdio.h>
# include <unistd.h>

extern "C" {
	#include "mlx.h"
}
#include "render.h"
#include "key_index.h"
# include "draw.h"

# include <iostream>

void noise_threading(t_env *env, double zoff);
void draw_noise_chunk(t_env *env, double zoff, int thread_id);

int	render(t_env *env)
{
	static double zoff = 0.0;

	env->frame_time = get_elapsed_time(&env->frame_timer);
	start_timer(&env->frame_timer);

	if (env->frame_time < 50)
	{
		usleep((50 - env->frame_time) * 1000);
	}

	// printf("frame_time: %zu\n", env->frame_time);

	updates(env);

	// Clear the image
	// clean_screen(env);

	// Draw the image
	noise_threading(env, zoff);
	// zoff += 0.01;

	// // draw test ----------------------------------
	// draw_circle(&env->img, (t_v2d_i){WIDTH / 2, HEIGHT / 2}, 100, (t_color){0x00FF00});
	// // // draw_rectangle(&env->img, (t_v2d_i){WIDTH / 2, HEIGHT / 2}, (t_v2d_i){100, 100}, (t_color){0x00FF00});

	// draw_line(&env->img, (t_v2d_i){0, 0}, (t_v2d_i){WIDTH, HEIGHT}, (t_color){0xFF0000});
	// draw_line(&env->img, (t_v2d_i){0, HEIGHT}, (t_v2d_i){WIDTH, 0}, (t_color){0xFF0000});

	// draw_line(&env->img, (t_v2d_i){WIDTH / 2, 0}, (t_v2d_i){WIDTH / 2, HEIGHT}, (t_color){0x0000FF});
	// draw_line(&env->img, (t_v2d_i){0, HEIGHT / 2}, (t_v2d_i){WIDTH, HEIGHT / 2}, (t_color){0x0000FF});
	// // --------------------------------------------
	
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	return (0);
}

// t_color lerp_color(t_color color1, t_color color2, double t)
// {
// 	t_color color;
// 	color.argb = 0;
// 	color.r = (uint8_t)(color1.r + (color2.r - color1.r) * t);
// 	color.g = (uint8_t)(color1.g + (color2.g - color1.g) * t);
// 	color.b = (uint8_t)(color1.b + (color2.b - color1.b) * t);
// 	return (color);
// }

void noise_threading(t_env *env, double zoff)
{
	for (int thread_id = 0; thread_id < env->nb_threads; thread_id++)
	{
		env->threads[thread_id] = std::thread(draw_noise_chunk, env, zoff, thread_id);
	}

	for (int thread_id = 0; thread_id < env->nb_threads; thread_id++)
	{
		env->threads[thread_id].join();
	}
}

void draw_noise_chunk(t_env *env, double zoff, int thread_id) {
	static t_color color1 = {0x2d41b3};
	static t_color color2 = {0x4d9fe4};
	static double water_level = 0.45;
	static t_color biomes[2][4] = {	// 0: land, 1: water => 0: cold-wet, 1: cold-dry, 2: hot-wet, 3: hot-dry
		{{0xe4f4e3}, {0xcacaca}, {0x8bb64d}, {0xeadd9c}},
		{{0x5e8dc2}, {0x5e8dc2}, {0x269daf}, {0x269daf}}
	};
	static double min = 1.0;
	static double max = -1.0;
	t_color color;

	double scale = env->camera_zoom;
	double xoff = env->camera_pos.x;
	double yoff = env->camera_pos.y;
	int y0 = thread_id * (env->mlx_info.res.y / env->nb_threads);
	int y1 = (thread_id + 1) * (env->mlx_info.res.y / env->nb_threads);
	while (y0 < y1)
	{
		for (int x = 0; x < env->mlx_info.res.x; x++)
		{
			double nx = ((double)x / env->mlx_info.res.x - 0.5) * scale + xoff;
			double ny = ((double)y0 / env->mlx_info.res.y - 0.5) * scale + yoff;
			// double nx = (double)x;
			// double ny = (double)y;
			double nz = 0.0 * scale + zoff;
			
			// double continentalness_noise = env->perlin[NOISE_CONTINENTS].noise(nx, ny, nz);
			double continentalness_noise = env->noise[NOISE_CONTINENTS].sample(nx, ny, nz);

			// if (continentalness_noise < min) {
			// 	min = continentalness_noise;
			// }

			// if (continentalness_noise > max) {
			// 	max = continentalness_noise;
			// }

			double erosion_noise = env->noise[NOISE_EROSION].sample(nx, ny, nz);

			double temperature_noise = env->noise[NOISE_TEMPERATURE].sample(nx, ny, nz);

			double vegetation_noise = env->noise[NOISE_VEGETATION].sample(nx, ny, nz);

			double ridges_noise = env->noise[NOISE_RIDGES].sample(nx, ny, nz);

			double ridges_folded = 1.0 - fabs(3.0 * fabs(ridges_noise) - 2.0);
			
			// #FDE725
			if (env->flags == NOISE_CONTINENTS) {
				if (continentalness_noise < 0) {
					put_pixel(&env->img, x, y0, lerp_color((t_color){0x440154}, (t_color){0x238A8D}, continentalness_noise / env->noise[NOISE_CONTINENTS].maxValue + 1.0));
				} else {
					put_pixel(&env->img, x, y0, lerp_color((t_color){0x238A8D}, (t_color){0xFDE725}, continentalness_noise / env->noise[NOISE_CONTINENTS].maxValue));
				}
			} else if (env->flags == NOISE_EROSION) {
				if (erosion_noise < 0) {
					put_pixel(&env->img, x, y0, lerp_color((t_color){0x440154}, (t_color){0x238A8D}, erosion_noise / env->noise[NOISE_EROSION].maxValue + 1.0));
				} else {
					put_pixel(&env->img, x, y0, lerp_color((t_color){0x238A8D}, (t_color){0xFDE725}, erosion_noise / env->noise[NOISE_EROSION].maxValue));
				}
			} else if (env->flags == NOISE_TEMPERATURE) {
				if (temperature_noise  < 0) {
					put_pixel(&env->img, x, y0, lerp_color((t_color){0x440154}, (t_color){0x238A8D}, temperature_noise  / env->noise[NOISE_TEMPERATURE].maxValue + 1.0));
				} else {
					put_pixel(&env->img, x, y0, lerp_color((t_color){0x238A8D}, (t_color){0xFDE725}, temperature_noise  / env->noise[NOISE_TEMPERATURE].maxValue));
				}
			} else if (env->flags == NOISE_VEGETATION) {
				if (vegetation_noise  < 0) {
					put_pixel(&env->img, x, y0, lerp_color((t_color){0x440154}, (t_color){0x238A8D}, vegetation_noise  / env->noise[NOISE_VEGETATION].maxValue + 1.0));
				} else {
					put_pixel(&env->img, x, y0, lerp_color((t_color){0x238A8D}, (t_color){0xFDE725}, vegetation_noise  / env->noise[NOISE_VEGETATION].maxValue));
				}
			} else if (env->flags == NOISE_RIDGES) {
				if (env->pv) {
					if (ridges_folded < 0) {
						put_pixel(&env->img, x, y0, lerp_color((t_color){0x440154}, (t_color){0x238A8D}, ridges_folded + 1.0));
					} else {
						put_pixel(&env->img, x, y0, lerp_color((t_color){0x238A8D}, (t_color){0xFDE725}, ridges_folded));
					}
				} else {
					if (ridges_noise < 0) {
						put_pixel(&env->img, x, y0, lerp_color((t_color){0x440154}, (t_color){0x238A8D}, ridges_noise / env->noise[NOISE_RIDGES].maxValue + 1.0));
					} else {
						put_pixel(&env->img, x, y0, lerp_color((t_color){0x238A8D}, (t_color){0xFDE725}, ridges_noise / env->noise[NOISE_RIDGES].maxValue));
					}
				}
			}
			
			// put_pixel(&env->img, x, y0, lerp_color((t_color){0}, (t_color){0xFFFFFF}, continentalness * 0.25 + 0.5));
		}
		y0++;
	}
	// std::cerr << "min: " << min << " ; max: " << max << std::endl;
}

