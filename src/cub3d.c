/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpac <vpac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:27:33 by lopayet-          #+#    #+#             */
/*   Updated: 2023/06/17 17:16:57 by vpac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_hooks(t_cub3d *cub3d);
static void	cub3d_free(t_cub3d *cub3d);

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	(void)argc;
	ft_bzero(&cub3d, sizeof(t_cub3d));
	if (cub3d_init_mlx(&cub3d) != 0)
		return (print_err("MLX error."), 1);
	if (parse_file(argv[1], &cub3d.parse) != 0)
		return (print_parsing_error(cub3d.parse.parse_errno),
			cub3d_free(&cub3d), 2);
	if (load_textures(&cub3d) != 0)
		return (print_err("Invalid textures."),
			cub3d_free(&cub3d), 3);
	init_player_data(&cub3d);
	set_hooks(&cub3d);
	mlx_loop(cub3d.mlx);
	cub3d_free(&cub3d);
	if (cub3d.alloc_err)
		return (print_err("Memory allocation error."), 1);
	return (0);
}

static void	cub3d_free(t_cub3d *cub3d)
{
	free_parse_data(&cub3d->parse);
	cub3d_destroy_mlx(*cub3d);
}

static int	cub3d_loop(t_cub3d *cub3d)
{
	clear_frame(cub3d->frame);
	cub3d->ray_list = 0;
	draw_background(cub3d);
	if (cast_rays(cub3d) != 0)
	{
		cub3d->alloc_err = 1;
		return (mlx_loop_end(cub3d->mlx), 1);
	}
	draw_ray_list(cub3d);
	update_player_pos(cub3d);
	frame_draw_minimap(cub3d);
	put_frame_to_window(cub3d);
	if (cub3d->ray_list)
		free(cub3d->ray_list);
	if (cub3d->exit)
		mlx_loop_end(cub3d->mlx);
	return (0);
}

static void	set_hooks(t_cub3d *cub3d)
{
	cub3d->exit = 0;
	mlx_loop_hook(cub3d->mlx, &cub3d_loop, cub3d);
	mlx_hook(cub3d->window, KeyRelease, KeyReleaseMask, &handle_keyup, cub3d);
	mlx_hook(cub3d->window, KeyPress, KeyPressMask, &handle_keydown, cub3d);
	mlx_hook(cub3d->window, DestroyNotify, NoEventMask,
		&handle_window_kill, cub3d);
}
