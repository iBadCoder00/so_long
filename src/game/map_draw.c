/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavila- <adavila-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:30:22 by adavila-          #+#    #+#             */
/*   Updated: 2024/04/21 20:30:22 by adavila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_collectable(t_win *win, double frame, int x, int y)
{
	put_img(win, win->map->collect_sprite[(int) frame],
		(x * TILE_WIDTH) + X_OFFSET, (y * TILE_LENGTH) + Y_OFFSET);
}

void	render_exit(t_win *win)
{
	put_img(win, win->map->exit_sprite, win->map->exit_point.x * TILE_WIDTH,
		win->map->exit_point.y * TILE_LENGTH);
}

void	render_patrol(t_win *win)
{
	t_point			*p;
	t_list			*temp;
	static double	animation = 0;

	temp = win->map->monsters;
	if ((int) animation == 2)
		animation = 0;
	while (temp)
	{
		p = temp->content;
		put_img(win, win->map->monster_sprite[(int) animation],
			p->x * TILE_WIDTH + M_XOFFSET, p->y * TILE_LENGTH + M_YOFFSET);
		temp = temp->next;
	}
	animation += 0.05;
}

void	render_map(t_win *win)
{
	int				i;
	int				j;
	static double	animation = 0;

	i = 0;
	j = 0;
	put_img(win, win->map->bg, 0, 0);
	while (i < win->map->x)
	{
		j = 0;
		while (j < win->map->y)
		{
			if ((win->map->map_table[j][i] == '1'
				&& j != 0 && i != 0) || j == win->map->y - 1)
				put_img(win, win->map->wall_sprite,
					i * TILE_WIDTH, j * TILE_LENGTH);
			else if (win->map->map_table[j][i] == 'C')
				render_collectable(win, animation, i, j);
			j++;
		}
		i++;
	}
	animation += 0.1;
	if ((int) animation == 6)
		animation = 0;
}
