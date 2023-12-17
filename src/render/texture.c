/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpac <vpac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:27:32 by vpac              #+#    #+#             */
/*   Updated: 2023/06/17 15:47:09 by vpac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_get_texture_data(t_cub3d *cub3d)
{
	cub3d->n_texture.frame.addr = mlx_get_data_addr(
			cub3d->n_texture.frame.mlx_img,
			&(cub3d->n_texture.frame.bpp), &(cub3d->n_texture.frame.line_len),
			&(cub3d->n_texture.frame.endian));
	cub3d->s_texture.frame.addr = mlx_get_data_addr(
			cub3d->s_texture.frame.mlx_img,
			&(cub3d->s_texture.frame.bpp), &(cub3d->s_texture.frame.line_len),
			&(cub3d->s_texture.frame.endian));
	cub3d->w_texture.frame.addr = mlx_get_data_addr(
			cub3d->w_texture.frame.mlx_img,
			&(cub3d->w_texture.frame.bpp), &(cub3d->w_texture.frame.line_len),
			&(cub3d->w_texture.frame.endian));
	cub3d->e_texture.frame.addr = mlx_get_data_addr(
			cub3d->e_texture.frame.mlx_img,
			&(cub3d->e_texture.frame.bpp), &(cub3d->e_texture.frame.line_len),
			&(cub3d->e_texture.frame.endian));
}

int	load_textures(t_cub3d *cub3d)
{
	cub3d->n_texture.frame.mlx_img = mlx_xpm_file_to_image(cub3d->mlx,
			cub3d->parse.no, &cub3d->n_texture.width, &cub3d->n_texture.height);
	cub3d->s_texture.frame.mlx_img = mlx_xpm_file_to_image(cub3d->mlx,
			cub3d->parse.so, &cub3d->s_texture.width, &cub3d->s_texture.height);
	cub3d->w_texture.frame.mlx_img = mlx_xpm_file_to_image(cub3d->mlx,
			cub3d->parse.we, &cub3d->w_texture.width, &cub3d->w_texture.height);
	cub3d->e_texture.frame.mlx_img = mlx_xpm_file_to_image(cub3d->mlx,
			cub3d->parse.ea, &cub3d->e_texture.width, &cub3d->e_texture.height);
	if (!cub3d->n_texture.frame.mlx_img || !cub3d->s_texture.frame.mlx_img
		|| !cub3d->w_texture.frame.mlx_img || !cub3d->e_texture.frame.mlx_img)
		return (1);
	load_get_texture_data(cub3d);
	return (0);
}

inline int	texture_get_pixel(t_texture texture, t_pixel_pos p)
{
	return (*(int *)(texture.frame.addr + (4) * (p.x + p.y * texture.width)));
}
