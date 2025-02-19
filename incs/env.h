#ifndef ENV_H
# define ENV_H

# include "envdef.h"
# include "key_index.h"
# include "color.h"
# include "ft_math.h"
# include "textures.h"

# include "PerlinNoise.h"
// # include "MinecraftNoise.h"
# include "MultiOctaveNoise.h"
# include "map.h"

#include <thread>
#include <sys/sysinfo.h>

typedef struct
{
	void	*img;
	t_color	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_ft_img; // mlx has t_img

typedef struct
{
	int		snum;
	t_v2d_i	res;
}	t_mlx_info;

typedef struct
{
	int		status;
	int		x;
	int		y;
	t_v2d_i	delta;
}	t_mouse;

typedef struct
{
	bool		key_pressed[KEY_COUNT];
	t_keystate	key_state[KEY_COUNT];
	bool		keyboard_used;
	t_mouse		mouse;
}	t_input;

typedef struct
{
	void						*mlx;
	void						*win;
	t_ft_img					img;
	t_mlx_info					mlx_info;
	t_input						input;
	size_t						frame_time;
	t_timer						frame_timer;
	t_v2d_d						camera_pos;
	float						camera_zoom;
	int							flags;
	int							pv;
	Random						rng;
	// MinecraftNoise			perlin[PERLIN_NOISE_COUNT];
	MultiOctaveNoise			noise[NOISE_COUNT];
	std::vector<BiomeRule_t>	biome_rules;
	std::thread					*threads;
	int							nb_threads;
	// Map							map;
}	t_env;

int		check_arguments(int ac, char **av);
int		init_env(t_env *env);
void	destroy_env(t_env *env);
int		open_mlx_window(t_env *env);

int		render(t_env *env);

#endif //MFAENV_H
