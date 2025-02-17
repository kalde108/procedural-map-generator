#ifndef COLOR_H
# define COLOR_H

# include <stdint.h>

typedef union
{
	uint32_t	argb;
	struct
	{
		uint8_t		b;
		uint8_t		g;
		uint8_t		r;
		uint8_t		a;
	};
}	t_color;

t_color lerp_color(t_color color1, t_color color2, double t);

#endif //COLOR_H
