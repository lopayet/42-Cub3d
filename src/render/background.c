/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpac <vpac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:27:00 by vpac              #+#    #+#             */
/*   Updated: 2023/06/17 15:44:22 by vpac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_background(t_cub3d *cub3d)
{
	t_pixel_pos	pix;
	int			ceiling_stop;

	ceiling_stop = WINDOW_HEIGHT / 2;
	pix.y = -1;
	while (++pix.y < ceiling_stop)
	{
		pix.x = -1;
		while (++pix.x < WINDOW_WIDTH)
			frame_draw_pixel(cub3d->frame, pix, cub3d->parse.cc);
	}
	while (++pix.y < WINDOW_HEIGHT)
	{
		pix.x = -1;
		while (++pix.x < WINDOW_WIDTH)
			frame_draw_pixel(cub3d->frame, pix, cub3d->parse.fc);
	}
}
