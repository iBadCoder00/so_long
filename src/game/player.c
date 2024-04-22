/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavila- <adavila-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:55:53 by adavila-          #+#    #+#             */
/*   Updated: 2024/04/15 13:55:53 by adavila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	update_x(t_player *player)
{
	player->x += (X_DX * player->x_direction);
	player->hb->right = (player->x + P_WIDTH) / TILE_WIDTH;
	player->hb->left = player->x / TILE_WIDTH;
}

static void	update_y(t_player *player)
{
	player->y_velocity = player->y_velocity + (player->gravity * GRAVITY_DT);
	player->y -= (player->y_velocity * V_DT);
	player->hb->top = player->y / TILE_LENGTH;
	player->hb->bottom = (player->y + P_LENGTH) / TILE_LENGTH;
}

static void	player_sprite(t_player *player)
{
	int				state;
	static double	i = 0;

	if (player->x_direction == 1)
		state = 0;
	else
		state = 1;
	if (player->is_moving && !player->is_airborne)
	{
		if (player->x_direction == 1)
			player->sprite = player->run_rsprite[(int) i];
		else
			player->sprite = player->run_lsprite[(int) i];
		i += 0.15;
	}
	else if (player->is_airborne && player->y_velocity < 0)
		player->sprite = player->airborne_sprite[state];
	else
	{
		player->sprite = player->idle_sprite[state];
		i = 0;
	}
	if ((int) i == 8)
		i = 0;
}

static void	check_collectable(t_win *win, char **map)
{
	if (map[win->player->hb->top][win->player->hb->left] == 'C')
	{
		map[win->player->hb->top][win->player->hb->left] = '0';
		win->map->n_collectables -= 1;
	}
	else if (map[win->player->hb->top][win->player->hb->right] == 'C')
	{
		map[win->player->hb->top][win->player->hb->right] = '0';
		win->map->n_collectables -= 1;
	}
	else if (map[win->player->hb->bottom][win->player->hb->left] == 'C')
	{
		map[win->player->hb->bottom][win->player->hb->left] = '0';
		win->map->n_collectables -= 1;
	}
	else if (map[win->player->hb->bottom][win->player->hb->right] == 'C')
	{
		map[win->player->hb->bottom][win->player->hb->right] = '0';
		win->map->n_collectables -= 1;
	}
}

void	update_player(t_win *win)
{
	if (win->player->is_moving)
		update_x(win->player);
	aabb_collision_x(win->player, win->map->map_table);
	if (win->player->is_airborne)
		update_y(win->player);
	aabb_collision_y(win->player, win->map->map_table);
	is_grounded(win->player, win->map->map_table);
	if (win->map->n_collectables > 0)
		check_collectable(win, win->map->map_table);
	if (win->map->n_collectables == 0
		&& is_hitbox(win->player, win->map->map_table, 'E'))
	{
		win->is_win = 1;
		ft_printf("You won!\n");
	}
	if (is_hitbox(win->player, win->map->map_table, 'M'))
	{
		ft_printf("You lost!\n");
		win->is_lost = 1;
	}
	player_sprite(win->player);
}
