/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:37:17 by lopayet-          #+#    #+#             */
/*   Updated: 2023/05/04 14:37:19 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_keydown(int keysym, t_cub3d *cub3d)
{
	if (keysym == XK_Escape)
		cub3d->exit = 1;
	if (keysym == XK_w)
		cub3d->player.move_forward = 1;
	if (keysym == XK_s)
		cub3d->player.move_backward = 1;
	if (keysym == XK_a)
		cub3d->player.move_left = 1;
	if (keysym == XK_d)
		cub3d->player.move_right = 1;
	if (keysym == XK_Left)
		cub3d->player.move_pa_left = 1;
	if (keysym == XK_Right)
		cub3d->player.move_pa_right = 1;
	return (0);
}

int	handle_keyup(int keysym, t_cub3d *cub3d)
{
	if (keysym == XK_w)
		cub3d->player.move_forward = 0;
	if (keysym == XK_s)
		cub3d->player.move_backward = 0;
	if (keysym == XK_a)
		cub3d->player.move_left = 0;
	if (keysym == XK_d)
		cub3d->player.move_right = 0;
	if (keysym == XK_Left)
		cub3d->player.move_pa_left = 0;
	if (keysym == XK_Right)
		cub3d->player.move_pa_right = 0;
	return (0);
}

int	handle_window_kill(t_cub3d *cub3d)
{
	cub3d->exit = 1;
	return (0);
}
