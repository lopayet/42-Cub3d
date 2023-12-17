/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpac <vpac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:56:20 by lopayet-          #+#    #+#             */
/*   Updated: 2023/06/17 15:26:39 by vpac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	clear_frame(t_frame frame)
{
	char	*pixel;
	int		total;
	int		i;

	total = (WINDOW_WIDTH * WINDOW_HEIGHT);
	pixel = frame.addr;
	i = 0;
	while (i < total)
	{
		*(int *)pixel = 0;
		pixel += 4;
		i++;
	}
}

inline void	frame_draw_pixel(t_frame frame, t_pixel_pos p, int color)
{
	*(int *)(frame.addr + (4) * (p.x + p.y * WINDOW_WIDTH)) = color;
}

void	put_frame_to_window(t_cub3d *cub3d)
{
	mlx_put_image_to_window(cub3d->mlx, cub3d->window,
		cub3d->frame.mlx_img, 0, 0);
}
