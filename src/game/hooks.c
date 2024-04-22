/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavila- <adavila-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:30:18 by adavila-          #+#    #+#             */
/*   Updated: 2024/04/21 20:30:18 by adavila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_press(int key, t_win *win)
{
	if (key == 'd')
	{
		win->player->x_direction = 1;
		win->player->is_moving = 1;
	}
	if (key == 'a')
	{
		win->player->x_direction = -1;
		win->player->is_moving = 1;
	}
	if (key == 's' && win->player->is_airborne)
		win->player->gravity = -1000;
	if (key == 'w')
	{
		if (!win->player->is_airborne)
		{
			win->player->movements += 1;
			win->player->gravity = GRAVITY;
			win->player->y_velocity = V_INIT;
			win->player->is_airborne = 1;
		}
	}
	return (1);
}

int	key_release(int key, t_win *win)
{
	if (key == 'q')
	{
		mlx_destroy_window(win->mlx, win->win);
		exit (0);
	}
	if (key == 'd')
		win->player->is_moving = 0;
	if (key == 'a')
		win->player->is_moving = 0;
	return (1);
}

int	close_window(t_win *win)
{
	mlx_destroy_window(win->mlx, win->win);
	exit (0);
}

void	_init_hooks(t_win *win)
{
	mlx_hook(win->win, KeyPress, KeyPressMask, key_press, win);
	mlx_hook(win->win, KeyRelease, KeyReleaseMask, key_release, win);
	mlx_hook(win->win, DestroyNotify, KeyPressMask, close_window, win);
}
