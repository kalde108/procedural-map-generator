SRCS_DIR = srcs/

SRC = \
	check_arguments \
	ft_itoalen \
	get_keyindex \
	main \
	MinecraftNoise \
	MultiOctaveNoise \
	PerlinNoise \
	Random \

# ********** ENV ********** #

SRC += $(addprefix $(ENV_DIR),$(ENV_SRC))

ENV_DIR = env/
ENV_SRC = \
	init_env \
	open_mlx_window \
	destroy_env \

# ********** COLOR ********** #

SRC += $(addprefix $(COLOR_DIR),$(COLOR_SRC))

COLOR_DIR = color/
COLOR_SRC = \
	lerp_color \

# ********** DRAW ********** #

SRC += $(addprefix $(DRAW_DIR),$(DRAW_SRC))

DRAW_DIR = draw/
DRAW_SRC = \
	clean_screen \
	draw_circle \
	draw_img \
	draw_img_a \
	draw_line \
	draw_triangle \
	put_pixel \
	put_pixel_alpha \
	draw_rectangle \

# ********** SEGMENTS ********** #

SRC += $(addprefix $(SEGMENTS_DIR),$(SEGMENTS_SRC))

SEGMENTS_DIR = $(DRAW_DIR)segments/
SEGMENTS_SRC = \
	draw_num_char \
	draw_num_int \
	get_num_arr \

# ********** HOOK ********** #

SRC += $(addprefix $(HOOK_DIR),$(HOOK_SRC))

HOOK_DIR = hook/
HOOK_SRC = \
	focusout_hook \
	keydown_hook \
	keyup_hook \
	mouse_hooks \

# ********** MATH ********** #

SRC += $(addprefix $(MATH_DIR),$(MATH_SRC))

MATH_DIR = math/
MATH_SRC = \
	complex \
	Vector2 \
	Vector3 \

# ********* RENDER ********* #

SRC += $(addprefix $(RENDER_DIR),$(RENDER_SRC))

RENDER_DIR = render/
RENDER_SRC = \
	render \

# ********** TIME ********** #

SRC += $(addprefix $(TIME_DIR),$(TIME_SRC))

TIME_DIR = time/
TIME_SRC = \
	get_elapsed_time \
	get_time \
	init_timer \
	start_timer \
	timer_is_over \

# ********* UPDATE ********* #

SRC += $(addprefix $(UPDATE_DIR),$(UPDATE_SRC))

UPDATE_DIR = update/
UPDATE_SRC = \
	update_input \
	update_mouse \
	updates \

SRCS := $(addsuffix .cpp, $(SRC))
