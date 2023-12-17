/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpac <vpac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:37:07 by vpac              #+#    #+#             */
/*   Updated: 2023/06/17 15:37:28 by vpac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	line_is_map_content(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '1')
		return (1);
	return (0);
}

void	set_parse_errno(t_parse_data *parse_data, int n)
{
	parse_data->parse_errno = n;
}

void	print_parsing_error(int err)
{
	ft_putstr_fd("Error\n", 2);
	if (err == 1)
		ft_putstr_fd("Can't open file.\n", 2);
	if (err == 2)
		ft_putstr_fd("File is not a .cub file.\n", 2);
	if (err == 3)
		ft_putstr_fd("Invalid data line.\n", 2);
	if (err == 4)
		ft_putstr_fd("Missing data line.\n", 2);
	if (err == 5)
		ft_putstr_fd("Duplicate data line.\n", 2);
	if (err == 6)
		ft_putstr_fd("Trailing characters after data line.\n", 2);
	if (err == 7)
		ft_putstr_fd("Wrong color format.\n", 2);
	if (err == 8)
		ft_putstr_fd("Trailing data after map end.\n", 2);
	if (err == 9)
		ft_putstr_fd("Invalid characters in map.\n", 2);
	if (err == 10)
		ft_putstr_fd("Map is not enclosed by walls.\n", 2);
	if (err == 11)
		ft_putstr_fd("Map has no starting point.\n", 2);
	if (err == 12)
		ft_putstr_fd("Map has more than one starting point.\n", 2);
}

void	dump_map(t_parse_data *parse_data)
{
	int		**map;
	int		i;
	char	c;

	map = parse_data->map;
	while (*map)
	{
		i = -1;
		while (++i < parse_data->map_w)
		{
			c = (char)map[0][i] + '0';
			write(1, &c, 1);
		}
		map++;
		write(1, "\n", 1);
	}
	return ;
}
