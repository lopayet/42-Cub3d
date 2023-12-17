/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpac <vpac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:07:48 by vpac              #+#    #+#             */
/*   Updated: 2023/06/17 17:15:46 by vpac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_texturing_data	t_texturing_data;
struct s_texturing_data
{
	int			t_off;
	t_pixel_pos	src;
	t_pixel_pos	dst;
	t_cub3d		*data;
	t_texture	*texture;
};

static void			draw_texture_pillar(t_ray_data ray,
						t_texturing_data *t_data);
static t_texture	*get_ray_texture(t_cub3d *data, t_ray_data ray);
static int			get_ray_hit_pos(t_ray_data ray);
static void			frame_draw_texture_line(t_texturing_data *text_data,
						t_pixel_pos window_src, int window_line_h,
						int texture_x);

void	draw3d(t_cub3d *data, t_ray_data ray, int ray_num)
{
	int					lineh;
	float				disw;
	int					lineo;
	float				ca;
	t_texturing_data	text_data;

	text_data.t_off = 0;
	ca = data->player.pa - ray.ra;
	disw = (cos(ca)) * (cos(ray.ra) * (ray.rx - data->player.pdx)
			- sin(ray.ra) * (ray.ry - data->player.pdy));
	lineh = (RES * WINDOW_HEIGHT) / disw;
	if (lineh > WINDOW_HEIGHT)
	{
		text_data.t_off = (lineh - WINDOW_HEIGHT) / 2;
		lineh = WINDOW_HEIGHT;
	}
	lineo = WINDOW_HEIGHT - (WINDOW_HEIGHT / 2 - lineh / 2);
	text_data.src.x = ray_num;
	text_data.src.y = lineo - lineh;
	text_data.dst.x = text_data.src.x + 1;
	text_data.dst.y = lineo;
	text_data.data = data;
	ray.texture = get_ray_texture(text_data.data, ray);
	draw_texture_pillar(ray, &text_data);
}

static void	draw_texture_pillar(t_ray_data ray, t_texturing_data *text_data)
{
	int			height;
	int			ray_hit_pos;

	text_data->texture = ray.texture;
	ray_hit_pos = get_ray_hit_pos(ray);
	height = text_data->dst.y - text_data->src.y;
	while (text_data->src.x < text_data->dst.x)
	{
		frame_draw_texture_line(text_data, text_data->src, height, ray_hit_pos);
		text_data->src.x++;
	}
}

static void	frame_draw_texture_line(t_texturing_data *text_data,
	t_pixel_pos window_src, int window_line_h, int texture_x)
{
	t_pixel_pos	window_pos;
	t_pixel_pos	texture_pos;
	int			i;

	i = 0;
	window_pos.x = window_src.x;
	window_pos.y = window_src.y;
	texture_pos.x = texture_x;
	while (i < window_line_h)
	{
		texture_pos.y = (float)(i + text_data->t_off)
			/ (window_line_h + text_data->t_off * 2)
			* (text_data->texture->height);
		frame_draw_pixel(text_data->data->frame, window_pos,
			texture_get_pixel(*(text_data->texture), texture_pos));
		window_pos.y++;
		i++;
	}
}

static int	get_ray_hit_pos(t_ray_data ray)
{
	int	width;

	width = ray.texture->width;
	if (ray.hit_horizontal)
	{
		if (ray.yo > 0.0)
			return (width - ((int)(ray.rx / RES * width) % width) - 1);
		return (((int)(ray.rx / RES * width) % width));
	}
	if (ray.xo > 0.0)
		return (((int)(ray.ry / RES * width) % width));
	return (width - ((int)(ray.ry / RES * width) % width) - 1);
}

static t_texture	*get_ray_texture(t_cub3d *data, t_ray_data ray)
{
	if (ray.hit_horizontal)
	{
		if (ray.yo > 0.0)
			return (&data->s_texture);
		return (&data->n_texture);
	}
	if (ray.xo > 0.0)
		return (&data->e_texture);
	return (&data->w_texture);
}
