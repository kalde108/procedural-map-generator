/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:46:31 by kchillon          #+#    #+#             */
/*   Updated: 2024/10/26 12:05:43 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	put_pixel_alpha(t_ft_img *img, int x, int y, t_color color)
{
	t_color	*dst;
	t_color	tmp;
	float	alpha;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = img->addr + y * WIDTH + x;
	tmp = *dst;
	alpha = (float)color.a / 255.0;
	dst->r += (color.r - tmp.r) * alpha;
	dst->g += (color.g - tmp.g) * alpha;
	dst->b += (color.b - tmp.b) * alpha;
}
