/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpac <vpac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:36:26 by vpac              #+#    #+#             */
/*   Updated: 2023/06/17 15:36:29 by vpac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_data_line_ogey(char *line)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \n");
	if (!trimmed)
		return (1);
	if (trimmed[0]
		&& !is_texture_line(trimmed) && !is_color_line(line))
		return (free(trimmed), 0);
	return (free(trimmed), 1);
}

static int	is_line_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!(line[i] == ' ' || line[i] == '\n'))
			return (0);
		i++;
	}
	return (1);
}

int	file_format_error(char *file, t_parse_data *parse_data)
{
	int		fd;
	char	*line;
	int		map_started;
	int		map_ended;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (set_parse_errno(parse_data, 1), 1);
	map_started = 0;
	map_ended = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!map_started)
			map_started = line_is_map_content(line);
		if (!map_started && !is_data_line_ogey(line))
			return (set_parse_errno(parse_data, 3), free(line), close(fd), 3);
		if (map_started && !line_is_map_content(line))
			map_ended = 1;
		if (map_ended && !is_line_empty(line))
			return (set_parse_errno(parse_data, 8), free(line), close(fd), 1);
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), 0);
}

int	filename_has_cub_extension(char *filename)
{
	int	i;

	i = ft_strlen(filename);
	if (i < 4)
		return (0);
	if (filename[i - 1] == 'b' && filename[i - 2] == 'u'
		&& filename[i - 3] == 'c' && filename[i - 4] == '.')
		return (1);
	return (0);
}
