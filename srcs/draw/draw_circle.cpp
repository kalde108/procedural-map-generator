#include "env.h"
#include "draw.h"

void draw_circle(t_ft_img *img, t_v2d_i pos, int radius, t_color color)
{
	for (int y = -radius; y <= radius; y++)
	{
		for (int x = -radius; x <= radius; x++)
		{
			if (x * x + y * y <= radius * radius)
				put_pixel(img, pos.x + x, pos.y + y, color);
		}
	}
}
