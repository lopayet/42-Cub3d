/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:59:22 by lopayet-          #+#    #+#             */
/*   Updated: 2023/05/04 15:44:06 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	frame_draw_line_right(t_frame frame, t_pixel_pos p1, t_pixel_pos p2,
	int color)
{
	t_pixel_pos	pixel;
	int			fraction;
	int			fraction_incr;
	int			step_y;

	step_y = ((p2.y - p1.y) >= 0) * 2 - 1;
	pixel.x = p1.x;
	pixel.y = p1.y;
	fraction_incr = 2 * ft_abs(p2.y - p1.y);
	fraction = fraction_incr - ft_abs(p2.x - p1.x);
	frame_draw_pixel(frame, pixel, color);
	while (pixel.x < p2.x)
	{
		fraction += fraction_incr;
		if (fraction >= 0)
		{
			pixel.y += step_y;
			fraction -= 2 * ft_abs(p2.x - p1.x);
		}
		pixel.x++;
		frame_draw_pixel(frame, pixel, color);
	}
}

static void	frame_draw_line_down(t_frame frame, t_pixel_pos p1, t_pixel_pos p2,
	int color)
{
	t_pixel_pos	pixel;
	int			fraction;
	int			fraction_incr;
	int			step_x;

	step_x = ((p2.x - p1.x) >= 0) * 2 - 1;
	pixel.x = p1.x;
	pixel.y = p1.y;
	fraction_incr = 2 * ft_abs(p2.x - p1.x);
	fraction = fraction_incr - ft_abs(p2.y - p1.y);
	frame_draw_pixel(frame, pixel, color);
	while (pixel.y < p2.y)
	{
		fraction += fraction_incr;
		if (fraction >= 0)
		{
			pixel.x += step_x;
			fraction -= 2 * ft_abs(p2.y - p1.y);
		}
		pixel.y++;
		frame_draw_pixel(frame, pixel, color);
	}
}

void	frame_draw_line(t_frame frame,
	t_pixel_pos p1, t_pixel_pos p2, int color)
{
	int	dx;
	int	dy;
	int	abs_dx;
	int	abs_dy;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	abs_dx = ft_abs(dx);
	abs_dy = ft_abs(dy);
	if (dx >= 0 && abs_dx >= abs_dy)
		frame_draw_line_right(frame, p1, p2, color);
	if (dx < 0 && abs_dx >= abs_dy)
		frame_draw_line_right(frame, p2, p1, color);
	if (dy >= 0 && abs_dx < abs_dy)
		frame_draw_line_down(frame, p1, p2, color);
	if (dy < 0 && abs_dx < abs_dy)
		frame_draw_line_down(frame, p2, p1, color);
}
