/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavila- <adavila-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:55:16 by adavila-          #+#    #+#             */
/*   Updated: 2024/04/15 13:55:16 by adavila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	aabb_collision_x(t_player *player, char **map)
{
	int	x_offset;

	x_offset = 0;
	if (is_hitbox(player, map, '1'))
	{
		if (player->x_direction == 1)
		{
			x_offset = ((player->hb->right * TILE_WIDTH)
					- (player->x + P_WIDTH));
			player->hb->right -= 1;
		}
		else
		{
			x_offset = (player->hb->left * TILE_WIDTH)
				+ (TILE_WIDTH - player->x);
			player->hb->left += 1;
		}
		player->x += x_offset;
	}
	else if (player->is_moving)
		player->movements += 1;
}

void	aabb_collision_y(t_player *player, char **map)
{
	int	y_offset;

	y_offset = 0;
	if (is_hitbox(player, map, '1'))
	{
		if (player->y_velocity > 0)
		{
			y_offset = ((player->hb->top * TILE_LENGTH)
					+ TILE_LENGTH - player->y);
			player->hb->top += 1;
			player->y_velocity = 0;
		}
		else
		{
			y_offset = (player->hb->bottom * TILE_LENGTH)
				- (player->y + P_LENGTH);
			player->hb->bottom -= 1;
		}
		player->y += y_offset;
	}
}

void	is_grounded(t_player *player, char **map)
{
	int	bottom;

	bottom = (player->y + P_LENGTH + 1) / TILE_LENGTH;
	if (map[bottom][player->hb->left] == '1'
		|| map[bottom][player->hb->right] == '1')
	{
		player->y_velocity = 0;
		player->is_airborne = 0;
	}
	else
		player->is_airborne = 1;
}

int	is_hitbox(t_player *player, char **map, char hit_char)
{
	if (map[player->hb->top][player->hb->left] == hit_char
		|| map[player->hb->top][player->hb->right] == hit_char
		|| map[player->hb->bottom][player->hb->left] == hit_char
		|| map[player->hb->bottom][player->hb->right] == hit_char)
		return (1);
	else
		return (0);
}
