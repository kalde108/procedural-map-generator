#ifndef ENVDEF_H
# define ENVDEF_H

# define WIN_NAME	"Map Generator"

#  define WIDTH			896
#  define HEIGHT		896

// # define FRAME_TIME	0.008333333333333333	// 120 fps
# define FRAME_TIME	0.016666666666666666		// 60 fps
// # define FRAME_TIME	0.03333333333333333		// 30 fps

# define FPS_BUFFER 20

// COLORS
# define MA_BLACK				0x000000
# define MA_WHITE				0xFFFFFF
# define MA_RED					0xFF0000
# define MA_GREEN				0x00FF00
# define MA_BLUE				0x0000FF
# define MA_YELLOW				0xFFFF00
# define MA_CYAN				0x00FFFF
# define MA_MAGENTA				0xFF00FF

# define MA_PLAYER_COLOR		0x0feabf
# define MA_WALL_COLOR			MA_WHITE
# define MA_FLOOR_COLOR			MA_BLACK
# define MA_BACKGROUND_COLOR	0x222222
# define MA_ENTRANCE_COLOR		MA_GREEN
# define MA_EXIT_COLOR			MA_RED

//ERROR MESSAGES
# define SCENE_ERR 	"Error\n%s\n"
# define SCENE_ERR2 "Error\n%s: %s\n"
# define SCENE_ERR3 "Error\n%s: %s: %s\n"
# define MAZE_ERR 	"Error\nMAZE: %s\n"
# define MAZE_ERR2 	"Error\nMAZE: %c: %s\n"
# define MLX_ERR 	"Error\nminilibx: %s: %s\n"
# define MLX_ERR2 	"Error\nminilibx: %s\n"
# define FATAL 		"Fatal"

#endif //ENVDEF_H
