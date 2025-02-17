#include "draw.h"

#include <stdio.h>

void	draw_img_a(t_color *img, t_ft_img *screen, t_v2d_i res, t_v2d_i camera_pos, float camera_zoom)
{
	int i = 0;
	t_v2d_i screen_pos = {0};
	int x = 0;
	int y = 0;
	t_v2d_i offset = {res.x / 2, res.y / 2};
	int zoom = (int)camera_zoom;

	while (i < res.x * res.y)
	{

		for (y = 0; y < zoom; y++)
		{
			for (x = 0; x < zoom; x++)
			{
				put_pixel_alpha(screen, (screen_pos.x - offset.x) * zoom + x + camera_pos.x, (screen_pos.y - offset.y) * zoom + y + camera_pos.y, img[i]);
			}
		}
		screen_pos.x++;
		if (screen_pos.x >= res.x)
		{
			screen_pos.x = 0;
			screen_pos.y++;
		}
		i++;
	}
}
