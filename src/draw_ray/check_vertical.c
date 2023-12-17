/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_vertical.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpac <vpac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 17:13:32 by vpac              #+#    #+#             */
/*   Updated: 2023/06/19 16:52:49 by vpac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_distance_to_hor_wall(t_player_data *player, t_ray_data *ray,
						float atan)
{
	if (cos(ray->ra) < 0.00001)
	{
		ray->rx = (((int)player->pdx >> 6) << 6) - 0.001;
		ray->ry = ((player->pdx - ray->rx) * atan + player->pdy);
		ray->xo = -RES;
		ray->yo = -ray->xo * atan;
	}
	else
	{
		ray->rx = (((int)player->pdx >> 6) << 6) + RES;
		ray->ry = ((player->pdx - ray->rx) * atan + player->pdy);
		ray->xo = RES;
		ray->yo = -ray->xo * atan;
	}
}

static int	is_in_map(int x, int y, int w, int h)
{
	return (
		(x > 0 && y > 0) && (x < w && y < h)
	);
}

t_ray_data	*check_for_vertical_wall(t_cub3d *data, t_ray_data *ray_elem)
{
	t_ray_data		*ray;
	t_player_data	*player;
	float			atan;
	int				ok;

	ok = 0;
	ray = ray_elem;
	atan = tan(ray->ra);
	player = &(data->player);
	get_distance_to_hor_wall(player, ray, atan);
	while (!ok)
	{
		ray->mx = (int)(ray->rx) >> 6;
		ray->my = (int)(ray->ry) >> 6;
		if ((is_in_map(ray->mx, ray->my, data->parse.map_w, data->parse.map_h)
				&& data->parse.map[ray->my][ray->mx] == 2)
		|| !is_in_map(ray->mx, ray->my, data->parse.map_w, data->parse.map_h))
			ok = 1;
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
		}
	}
	return (ray);
}
