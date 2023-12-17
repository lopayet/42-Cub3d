/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpac <vpac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:36:33 by lopayet-          #+#    #+#             */
/*   Updated: 2023/06/17 15:44:22 by vpac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	fill_parse_data_from_line(char *line, t_parse_data *parse_data);

int	get_data_from_file(char *file, t_parse_data *parse_data)
{
	int		fd;
	char	*line;
	char	*trimmed_line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		trimmed_line = ft_strtrim(line, " \n");
		if (!trimmed_line)
			return (free(line), close(fd), 1);
		if (fill_parse_data_from_line(trimmed_line, parse_data) != 0)
			return (free(trimmed_line), free(line), close(fd), 1);
		free(trimmed_line);
		free(line);
		line = get_next_line(fd);
	}
	if (have_missing_data(parse_data))
		return (set_parse_errno(parse_data, 4), close(fd), 1);
	return (close(fd), 0);
}

static int	fill_color_data_from_line_split(char **line_split,
	t_parse_data *parse_data)
{
	char	**color_split;

	color_split = ft_split(line_split[1], ',');
	if (!color_split)
		return (1);
	if (!color_split[0] || !color_split[1]
		|| !color_split[2] || color_split[3]
		|| !is_color_valid(color_split))
		return (ft_split_free(color_split), set_parse_errno(parse_data, 7), 1);
	if (!ft_strncmp(line_split[0], "F", 1))
	{
		parse_data->fc = (ft_atoi(color_split[0]) << 16)
			+ (ft_atoi(color_split[1]) << 8) + (ft_atoi(color_split[2]));
		parse_data->fc_set = 1;
	}
	if (!ft_strncmp(line_split[0], "C", 1))
	{
		parse_data->cc = (ft_atoi(color_split[0]) << 16)
			+ (ft_atoi(color_split[1]) << 8) + (ft_atoi(color_split[2]));
		parse_data->cc_set = 1;
	}
	if (line_split[2])
		return (set_parse_errno(parse_data, 6),
			ft_split_free(color_split), 1);
	return (ft_split_free(color_split), 0);
}

static int	fill_texture_data_from_line_split(char **line_split,
				t_parse_data *parse_data)
{
	if (!ft_strncmp(line_split[0], "NO ", 2))
		parse_data->no = ft_strdup(line_split[1]);
	if (!ft_strncmp(line_split[0], "SO ", 2))
		parse_data->so = ft_strdup(line_split[1]);
	if (!ft_strncmp(line_split[0], "WE ", 2))
		parse_data->we = ft_strdup(line_split[1]);
	if (!ft_strncmp(line_split[0], "EA ", 2))
		parse_data->ea = ft_strdup(line_split[1]);
	if (line_split[2])
		return (set_parse_errno(parse_data, 6), 1);
	return (0);
}

static int	is_line_duplicate(char *line, t_parse_data *parse_data)
{
	if (!ft_strncmp(line, "NO ", 3) && parse_data->no)
		return (1);
	if (!ft_strncmp(line, "SO ", 3) && parse_data->so)
		return (1);
	if (!ft_strncmp(line, "WE ", 3) && parse_data->we)
		return (1);
	if (!ft_strncmp(line, "EA ", 3) && parse_data->ea)
		return (1);
	if (!ft_strncmp(line, "F ", 2) && parse_data->fc_set)
		return (1);
	if (!ft_strncmp(line, "C ", 2) && parse_data->cc_set)
		return (1);
	return (0);
}

static int	fill_parse_data_from_line(char *line, t_parse_data *parse_data)
{
	char	**line_split;

	if (is_line_duplicate(line, parse_data))
		return (set_parse_errno(parse_data, 5), 1);
	line_split = ft_split(line, ' ');
	if (!line_split)
		return (1);
	if (!line_split[0] || !line_split[1])
		return (ft_split_free(line_split), 0);
	if (is_texture_line(line))
		if (fill_texture_data_from_line_split(line_split, parse_data) != 0)
			return (ft_split_free(line_split), 1);
	if (is_color_line(line))
		if (fill_color_data_from_line_split(line_split, parse_data) != 0)
			return (ft_split_free(line_split), 1);
	return (ft_split_free(line_split), 0);
}
