/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:50:48 by ibertran          #+#    #+#             */
/*   Updated: 2024/10/27 16:55:58 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "env.h"

void	clean_screen(t_env *env);
void	put_pixel(t_ft_img *img, int x, int y, t_color color);
void	put_pixel_alpha(t_ft_img *img, int x, int y, t_color color);
void	draw_img_a(t_color *img, t_ft_img *screen, t_v2d_i res, t_v2d_i camera_pos, float camera_zoom);
void	draw_img(t_color *img, t_ft_img *screen, t_v2d_i res, t_v2d_i camera_pos, float camera_zoom);
void	draw_circle(t_ft_img *img, t_v2d_i pos, int radius, t_color color);
void	draw_line(t_ft_img *img, t_v2d_i p1, t_v2d_i p2, t_color color);
void	draw_rectangle(t_ft_img *img, t_v2d_i pos, t_v2d_i size, t_color color);
void	draw_triangle(t_ft_img *img, t_triangle tirangle, t_color color);
void	draw_num_int(t_ft_img *img, int number, t_v2d_i pos, int size, t_color color);
void	draw_num_char(t_ft_img *img, char *numbers, t_v2d_i pos, int size, t_color color);

#endif

/*

0110 0010
1001 1101

00001001 11010000
	9		208


13
00001101 10010000
	13		144

*/
