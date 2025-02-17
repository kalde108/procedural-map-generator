#include "color.h"

t_color lerp_color(t_color color1, t_color color2, double t)
{
	t_color color;
	color.argb = 0;
	color.r = (uint8_t)(color1.r + (color2.r - color1.r) * t);
	color.g = (uint8_t)(color1.g + (color2.g - color1.g) * t);
	color.b = (uint8_t)(color1.b + (color2.b - color1.b) * t);
	return (color);
}
