/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpac <vpac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:36:39 by vpac              #+#    #+#             */
/*   Updated: 2023/06/17 17:17:13 by vpac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	pitagora(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

static t_ray_data	check_for_shortest_line(t_player_data *p,
						t_ray_data h_inter, t_ray_data v_inter)
{
	float	dish;
	float	disv;

	dish = pitagora(p->pdx, p->pdy, h_inter.rx, h_inter.ry);
	disv = pitagora(p->pdx, p->pdy, v_inter.rx, v_inter.ry);
	if (dish > disv && dish != pitagora(p->pdx, p->pdy, p->pdx, p->pdy))
	{
		v_inter.hit_horizontal = 0;
		return (v_inter);
	}
	h_inter.hit_horizontal = 1;
	return (h_inter);
}

void	draw_ray_list(t_cub3d *data)
{
	int	i;
	int	ray_num;

	ray_num = 0;
	i = data->ray_count - 1;
	while (i >= 0)
	{
		draw3d(data, data->ray_list[i], ray_num);
		ray_num++;
		i--;
	}
}

double	get_ray_angle(t_cub3d *data, int window_x)
{
	double	ra_vec_x;
	double	ra_vec_y;
	double	pa_vec_x;
	double	pa_vec_y;
	double	camera_x;

	camera_x = 2 * window_x / (double)WINDOW_WIDTH - 1;
	pa_vec_x = cos(data->player.pa);
	pa_vec_y = sin(data->player.pa);
	ra_vec_x = pa_vec_x + data->player.plane_vec_x * camera_x;
	ra_vec_y = pa_vec_y + data->player.plane_vec_y * camera_x;
	return (atan2(ra_vec_y, ra_vec_x));
}

int	cast_rays(t_cub3d *data)
{
	t_ray_data		vertical_inter;
	t_ray_data		horizontal_inter;
	int				i;

	i = 0;
	data->ray_count = 0;
	data->ray_list = malloc(sizeof(t_ray_data) * (WINDOW_WIDTH) + 1);
	if (!data->ray_list)
		return (1);
	while (i < WINDOW_WIDTH)
	{
		data->ray_list[i].ra = get_ray_angle(data, i);
		horizontal_inter = *check_for_horizontal_wall(data, &data->ray_list[i]);
		vertical_inter = *check_for_vertical_wall(data, &data->ray_list[i]);
		data->ray_list[i] = check_for_shortest_line(&(data->player),
				horizontal_inter, vertical_inter);
		i++;
	}
	data->ray_count = WINDOW_WIDTH;
	return (0);
}
