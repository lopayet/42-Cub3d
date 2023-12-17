/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:44:53 by lopayet-          #+#    #+#             */
/*   Updated: 2023/05/04 15:43:56 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_map_row_from_line(int *row, char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == ' ')
			row[i] = 0;
		else if (line[i] == '0')
			row[i] = 1;
		else if (line[i] == '1')
			row[i] = 2;
		else if (line[i] == 'N')
			row[i] = 3;
		else if (line[i] == 'S')
			row[i] = 4;
		else if (line[i] == 'E')
			row[i] = 5;
		else if (line[i] == 'W')
			row[i] = 6;
		else
			row[i] = -1;
		i++;
	}
}

int	get_map_from_file(char *file, t_parse_data *parse_data)
{
	int		fd;
	char	*line;
	int		map_started;
	int		row;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (1);
	map_started = 0;
	row = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!map_started)
			map_started = line_is_map_content(line);
		if (map_started && !line_is_map_content(line))
			return (free(line), close(fd), 0);
		if (map_started)
			set_map_row_from_line(parse_data->map[row++], line);
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), 0);
}
