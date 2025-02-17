#include "draw.h"
#include "segment_display.h"

#include <stdio.h>

int	ft_itoalen(int n);

void draw_num_int(t_ft_img *img, int number, t_v2d_i pos, int size, t_color color)
{
	int len = ft_itoalen(number);
	int buff[10];
	for (int i = 0; i < len; i++)
	{
		buff[i] = number % 10;
		number /= 10;
	}
	for (int i = 0; i < len; i++)
	{
		int n = buff[len - i - 1];
		int *num_arr = get_num_arr(n);
		for (int j = 0; num_arr[j] != END; j++)
		{
			int *seg = segments[num_arr[j]];
			for (int k = 0; k < 4; k++)
			{
				t_v2d_d p1 = all_points[seg[k * 3]];
				t_v2d_d p2 = all_points[seg[k * 3 + 1]];
				t_v2d_d p3 = all_points[seg[k * 3 + 2]];
				draw_triangle(img, (t_triangle){(t_v2d_d){pos.x + p1.x * size, pos.y + p1.y * size},
												(t_v2d_d){pos.x + p2.x * size, pos.y + p2.y * size},
												(t_v2d_d){pos.x + p3.x * size, pos.y + p3.y * size}}, color);
			}
		}
		pos.x += 1.5 * size;
	}
}
