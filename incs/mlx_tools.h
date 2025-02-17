#ifndef MLX_TOOLS_H
# define MLX_TOOLS_H

# include "env.h"

// hook
int	keydown_hook(int keycode, t_env *mlx);
int	keyup_hook(int keycode, t_env *mlx);
int	buttonpress_hook(int button, int x, int y, t_env *env);
int	buttonrelease_hook(int button, int x, int y, t_env *env);
int	focusout_hook(t_env *env);
int	keydown_hook(int keycode, t_env *mlx);
int	keyup_hook(int keycode, t_env *mlx);

#endif //MLX_TOOLS_H
