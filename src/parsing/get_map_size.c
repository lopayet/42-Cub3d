/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:46:09 by lopayet-          #+#    #+#             */
/*   Updated: 2023/05/04 15:43:56 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_map_char(char c)
{
	return (c == '0' || c == '1'
		|| c == 'N' || c == 'S'
		|| c == 'E' || c == 'W');
}

static int	get_line_length(char *line)
{
	int	i;
	int	last_i;
	int	in_map_char;

	i = 0;
	last_i = 0;
	in_map_char = 0;
	while (line[i])
	{
		if (!is_map_char(line[i]) && in_map_char)
			last_i = i;
		in_map_char = is_map_char(line[i]);
		i++;
	}
	return (last_i);
}

static void	go_to_eof(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

int	get_map_size_from_file(char *file, t_parse_data *parse_data)
{
	int		fd;
	char	*line;
	int		map_started;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (1);
	map_started = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!map_started)
			map_started = line_is_map_content(line);
		if (map_started && !line_is_map_content(line))
			return (free(line), go_to_eof(fd), close(fd), 0);
		if (map_started)
			parse_data->map_h++;
		if (map_started && get_line_length(line) > parse_data->map_w)
			parse_data->map_w = get_line_length(line);
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), 0);
}
