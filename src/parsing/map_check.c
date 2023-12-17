/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpac <vpac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:35:17 by vpac              #+#    #+#             */
/*   Updated: 2023/06/17 15:35:20 by vpac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	map_has_invalid_blocks(t_parse_data *parse_data)
{
	int		**map;
	int		i;

	map = parse_data->map;
	while (*map)
	{
		i = -1;
		while (++i < parse_data->map_w)
			if (map[0][i] == -1)
				return (1);
		map++;
	}
	return (0);
}

static int	empty_space_is_enclosed(t_parse_data *parse_data, int x, int y)
{
	int		**map;

	if (x <= 0 || y <= 0
		|| x >= parse_data->map_w - 1
		|| y >= parse_data->map_h - 1)
		return (0);
	map = parse_data->map;
	if (!map[y - 1][x] || !map[y + 1][x]
		|| !map[y][x - 1] || !map[y][x + 1])
		return (0);
	return (1);
}

static int	map_has_holes(t_parse_data *parse_data)
{
	int		**map;
	int		x;
	int		y;

	y = -1;
	map = parse_data->map;
	while (map[++y])
	{
		x = -1;
		while (++x < parse_data->map_w)
			if ((map[y][x] == 1 || (map[y][x] >= 3 && map[y][x] <= 6))
				&& !empty_space_is_enclosed(parse_data, x, y))
				return (1);
	}
	return (0);
}

static int	get_spawnpoint_count(t_parse_data *parse_data)
{
	int		**map;
	int		x;
	int		y;
	int		count;

	count = 0;
	y = -1;
	map = parse_data->map;
	while (map[++y])
	{
		x = -1;
		while (++x < parse_data->map_w)
			if (map[y][x] >= 3 && map[y][x] <= 6)
				count++;
	}
	return (count);
}

int	is_map_valid(t_parse_data *parse_data)
{
	int	count;

	if (map_has_invalid_blocks(parse_data))
		return (set_parse_errno(parse_data, 9), 0);
	count = get_spawnpoint_count(parse_data);
	if (count == 0)
		return (set_parse_errno(parse_data, 11), 0);
	if (count > 1)
		return (set_parse_errno(parse_data, 12), 0);
	if (map_has_holes(parse_data))
		return (set_parse_errno(parse_data, 10), 0);
	return (1);
}
