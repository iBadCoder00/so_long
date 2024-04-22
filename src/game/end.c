/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavila- <adavila-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:55:35 by adavila-          #+#    #+#             */
/*   Updated: 2024/04/22 11:55:35 by adavila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	game_end(t_win *win)
{
	mlx_clear_window(win->mlx, win->win);
	if (win->is_win)
	{
		put_img(win, win->screen[0], ((win->map->x * TILE_WIDTH) - END_WIDTH)
			/ 2, ((win->map->y * TILE_LENGTH) - END_LENGTH) / 2);
	}
	else if (win->is_lost)
		put_img(win, win->screen[1], ((win->map->x * TILE_WIDTH) - END_WIDTH)
			/ 2, ((win->map->y * TILE_LENGTH) - END_LENGTH) / 2);
}
