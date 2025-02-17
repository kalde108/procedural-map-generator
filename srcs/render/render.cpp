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
	// static double min = 1.0;
	// static double max = -1.0;
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
			
			double height = (env->perlin[2].octaveNoise(nx, ny, nz, 8, 0.5));
			height = height * 0.5 + 0.5;

			color = lerp_color((t_color){0}, (t_color){0xFFFFFF}, (height + 1.0) * 0.5);

			int is_water = 0;
			if (height < water_level) {
				is_water = 1;
			}

			nz += 52.5;

			double temperature = (env->perlin[0].octaveNoise(nx, ny, nz, 8, 0.5));

			int is_cold = temperature < 0.0;

			nz += 52.5;

			double humidity = (env->perlin[1].octaveNoise(nx, ny, nz, 8, 0.5));

			int is_wet = humidity < 0.0;

			int climate = is_cold * 2 + is_wet;
			// printf("is_cold: %d, is_wet: %d, climate: %d\n", is_cold, is_wet, climate);
			color = biomes[is_water][climate];
			// put_pixel(&env->img, x, y0, color);

			// height map
			put_pixel(&env->img, x, y0, lerp_color((t_color){0}, (t_color){0xFFFFFF}, height));
		}
		y0++;
	}
}

