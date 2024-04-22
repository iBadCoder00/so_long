/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavila- <adavila-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:43:48 by adavila-          #+#    #+#             */
/*   Updated: 2024/04/18 21:43:48 by adavila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_scene(t_win *win)
{
	render_map(win);
	render_patrol(win);
	render_exit(win);
}

void	draw_player(t_win *win)
{
	update_player(win);
	put_img(win, win->player->sprite, win->player->x, win->player->y);
}

void	draw_ui(t_win *win)
{
	char	*movements;

	movements = ft_itoa(win->player->movements);
	put_img(win, win->map->hud_sprite, 0, 0);
	mlx_string_put(win->mlx, win->win,
		80, 20, 0xFFFFFF, movements);
	free(movements);
}
