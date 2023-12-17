/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpac <vpac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:09:15 by vpac              #+#    #+#             */
/*   Updated: 2023/06/17 17:03:45 by vpac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		player_move(t_cub3d *data, float x_add, float y_add);
static float	get_max_x_move(t_cub3d *data, float x_want);
static float	get_max_y_move(t_cub3d *data, float y_want);

void	update_player_pos(t_cub3d *data)
{
	if (data->player.move_pa_right)
		data->player.pa -= (float)PLAYER_ANGLE_SPEED / 100.0;
	if (data->player.move_pa_left)
		data->player.pa += (float)PLAYER_ANGLE_SPEED / 100.0;
	update_player_plane_vector(data);
	if (data->player.move_left)
		player_move(data,
			(float)PLAYER_SPEED * -sin(data->player.pa),
			(float)PLAYER_SPEED * -cos(data->player.pa));
	if (data->player.move_right)
		player_move(data,
			(float)PLAYER_SPEED * sin(data->player.pa),
			(float)PLAYER_SPEED * cos(data->player.pa));
	if (data->player.move_forward)
		player_move(data,
			(float)PLAYER_SPEED * cos(data->player.pa),
			(float)PLAYER_SPEED * -sin(data->player.pa));
	if (data->player.move_backward)
		player_move(data,
			(float)PLAYER_SPEED * -cos(data->player.pa),
			(float)PLAYER_SPEED * sin(data->player.pa));
}

void	update_player_plane_vector(t_cub3d *data)
{
	double	plane_angle;
	double	multiplier;

	multiplier = 0.75;
	plane_angle = data->player.pa + (PI / 2.0);
	data->player.plane_vec_x = cos(plane_angle) * multiplier;
	data->player.plane_vec_y = sin(plane_angle) * multiplier;
}

static void	player_move(t_cub3d *data, float x_add, float y_add)
{
	int		x_neg;
	int		y_neg;

	x_neg = x_add < 0;
	y_neg = y_add < 0;
	if (x_neg)
		x_add = -x_add;
	if (y_neg)
		y_add = -y_add;
	while (x_add > 0 || y_add > 0)
	{
		if (x_add > 0 && x_neg)
			data->player.pdx += get_max_x_move(data, -min_float(0.02, x_add));
		if (x_add > 0 && !x_neg)
			data->player.pdx += get_max_x_move(data, min_float(0.02, x_add));
		if (y_add > 0 && y_neg)
			data->player.pdy += get_max_y_move(data, -min_float(0.02, y_add));
		if (y_add > 0 && !y_neg)
			data->player.pdy += get_max_y_move(data, min_float(0.02, y_add));
		x_add -= 0.02;
		y_add -= 0.02;
	}
}

static float	get_max_x_move(t_cub3d *data, float x_want)
{
	int	map_y;
	int	map_x_want;

	if (x_want < 0)
		map_x_want = data->player.pdx + x_want - ((float)SLIDE_DISTANCE * RES);
	else
		map_x_want = data->player.pdx + x_want + ((float)SLIDE_DISTANCE * RES);
	map_x_want /= RES;
	map_y = data->player.pdy / (float)RES;
	if (data->parse.map[map_y][map_x_want] == 2)
		return (0);
	map_y = data->player.pdy / (float)RES + SLIDE_DISTANCE;
	if (data->parse.map[map_y][map_x_want] == 2)
		return (0);
	map_y = data->player.pdy / (float)RES - SLIDE_DISTANCE;
	if (data->parse.map[map_y][map_x_want] == 2)
		return (0);
	return (x_want);
}

static float	get_max_y_move(t_cub3d *data, float y_want)
{
	int	map_x;
	int	map_y_want;

	if (y_want < 0)
		map_y_want = data->player.pdy + y_want - ((float)SLIDE_DISTANCE * RES);
	else
		map_y_want = data->player.pdy + y_want + ((float)SLIDE_DISTANCE * RES);
	map_y_want /= RES;
	map_x = data->player.pdx / (float)RES;
	if (data->parse.map[map_y_want][map_x] == 2)
		return (0);
	map_x = data->player.pdx / (float)RES + SLIDE_DISTANCE;
	if (data->parse.map[map_y_want][map_x] == 2)
		return (0);
	map_x = data->player.pdx / (float)RES - SLIDE_DISTANCE;
	if (data->parse.map[map_y_want][map_x] == 2)
		return (0);
	return (y_want);
}
