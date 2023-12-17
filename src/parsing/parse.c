/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpac <vpac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:33:53 by lopayet-          #+#    #+#             */
/*   Updated: 2023/06/17 15:43:20 by vpac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_cub3d_map(int **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static int	allocate_map(t_parse_data *parse_data)
{
	int	i;

	parse_data->map = malloc(sizeof(int *) * (parse_data->map_h + 1));
	if (!parse_data->map)
		return (1);
	i = 0;
	while (i < parse_data->map_h)
	{
		parse_data->map[i] = malloc(sizeof(int) * parse_data->map_w);
		if (!parse_data->map[i])
			return (free_cub3d_map(parse_data->map), 1);
		ft_bzero((void *)parse_data->map[i], sizeof(int) * parse_data->map_w);
		i++;
	}
	parse_data->map[i] = 0;
	return (0);
}

void	free_parse_data(t_parse_data *parse_data)
{
	free_cub3d_map(parse_data->map);
	if (parse_data->no)
		free(parse_data->no);
	if (parse_data->so)
		free(parse_data->so);
	if (parse_data->we)
		free(parse_data->we);
	if (parse_data->ea)
		free(parse_data->ea);
}

int	parse_file(char *file, t_parse_data *parse_data)
{
	ft_bzero((void *)parse_data, sizeof(t_parse_data));
	if (!filename_has_cub_extension(file))
		return (set_parse_errno(parse_data, 2), 1);
	if (file_format_error(file, parse_data))
		return (1);
	if (get_data_from_file(file, parse_data) != 0)
		return (1);
	if (get_map_size_from_file(file, parse_data) != 0)
		return (1);
	if (allocate_map(parse_data) != 0)
		return (1);
	if (get_map_from_file(file, parse_data) != 0)
		return (1);
	if (!is_map_valid(parse_data))
		return (1);
	return (0);
}
