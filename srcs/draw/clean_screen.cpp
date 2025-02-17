#include "env.h"

void	clean_screen(t_env *env)
{
	register int			cursor;
	const int		max = (HEIGHT * (WIDTH >> 2));
	__int128_t				*img_ptr;
	static const __int128_t	min = (__int128_t)MA_BACKGROUND_COLOR << 96 | (__int128_t)MA_BACKGROUND_COLOR << 64 | (__int128_t)MA_BACKGROUND_COLOR << 32 | (__int128_t)MA_BACKGROUND_COLOR;

	img_ptr = (__int128_t *)env->img.addr;
	cursor = -1;
	while (++cursor < max)
	{
		img_ptr[cursor++] = min;
		img_ptr[cursor++] = min;
		img_ptr[cursor++] = min;
		img_ptr[cursor] = min;
	}	
}
