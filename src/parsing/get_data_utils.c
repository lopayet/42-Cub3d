/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpac <vpac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:37:20 by lopayet-          #+#    #+#             */
/*   Updated: 2023/06/17 15:44:22 by vpac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	have_missing_data(t_parse_data *parse_data)
{
	return (!(parse_data->no
			&& parse_data->so
			&& parse_data->we
			&& parse_data->ea
			&& parse_data->cc_set
			&& parse_data->fc_set));
}

int	is_texture_line(char *line)
{
	return (!ft_strncmp(line, "NO ", 3)
		|| !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3)
		|| !ft_strncmp(line, "EA ", 3));
}

int	is_color_line(char *line)
{
	return (!ft_strncmp(line, "F ", 2)
		|| !ft_strncmp(line, "C ", 2));
}

int	is_color_valid(char **split)
{
	int		i;
	int		j;
	char	*str;

	j = 0;
	while (j < 3)
	{
		str = split[j];
		i = -1;
		while (str[++i])
			if (!ft_isdigit(str[i]))
				return (0);
		i = ft_atoi(str);
		if (i > 255 || i < 0)
			return (0);
		j++;
	}
	return (1);
}
