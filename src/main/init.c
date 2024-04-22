/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavila- <adavila-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:56:58 by adavila-          #+#    #+#             */
/*   Updated: 2024/04/15 13:56:58 by adavila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	_init_sprites_(t_player *player, t_win *win)
{
	player->idle_sprite[0] = get_sprite(win, IDLE_R);
	player->idle_sprite[1] = get_sprite(win, IDLE_L);
	player->run_rsprite[0] = get_sprite(win, RUN_R1);
	player->run_rsprite[1] = get_sprite(win, RUN_R2);
	player->run_rsprite[2] = get_sprite(win, RUN_R3);
	player->run_rsprite[3] = get_sprite(win, RUN_R4);
	player->run_rsprite[4] = get_sprite(win, RUN_R5);
	player->run_rsprite[5] = get_sprite(win, RUN_R6);
	player->run_rsprite[6] = get_sprite(win, RUN_R7);
	player->run_rsprite[7] = get_sprite(win, RUN_R8);
	player->run_lsprite[0] = get_sprite(win, RUN_L1);
	player->run_lsprite[1] = get_sprite(win, RUN_L2);
	player->run_lsprite[2] = get_sprite(win, RUN_L3);
	player->run_lsprite[3] = get_sprite(win, RUN_L4);
	player->run_lsprite[4] = get_sprite(win, RUN_L5);
	player->run_lsprite[5] = get_sprite(win, RUN_L6);
	player->run_lsprite[6] = get_sprite(win, RUN_L7);
	player->run_lsprite[7] = get_sprite(win, RUN_L8);
	player->airborne_sprite[0] = get_sprite(win, AIR_R);
	player->airborne_sprite[1] = get_sprite(win, AIR_L);
}

static void	_init_player_(t_player *player, t_win *win)
{
	player->x = (win->map->starting_point.x * TILE_WIDTH);
	player->y = (win->map->starting_point.y * TILE_LENGTH);
	player->gravity = -500;
	player->is_moving = 0;
	player->movements = 0;
	player->is_airborne = 1;
	player->y_velocity = 0;
	player->x_direction = 1;
	player->hb->left = player->x / TILE_WIDTH;
	player->hb->right = (player->x + P_WIDTH) / TILE_WIDTH;
	player->hb->top = player->y / TILE_LENGTH;
	player->hb->bottom = (player->y + P_LENGTH) / TILE_LENGTH;
	_init_sprites_(player, win);
	player->sprite = player->idle_sprite[0];
}

static void	parse_map(t_map *map, char *map_path)
{
	int		fd;
	int		rd;
	char	*buffer;

	buffer = malloc(BUFF_SIZE);
	fd = check_format(map_path);
	rd = read(fd, buffer, BUFF_SIZE);
	if (rd < 0)
		ft_perror("Buffer reading error");
	buffer[rd] = 0;
	check_elements(map, buffer);
	free(buffer);
}

static void	_init_map_(t_win *win, char *map_path)
{
	win->map->x = 0;
	win->map->y = 0;
	win->map->n_exits = 0;
	win->map->n_starts = 0;
	win->map->map_table = 0;
	win->map->monsters = 0;
	win->map->exit_point.x = 0;
	win->map->exit_point.y = 0;
	win->map->n_collectables = 0;
	win->map->starting_point.x = 0;
	win->map->starting_point.y = 0;
	win->map->wall_sprite = get_sprite(win, WALL);
	win->map->bg = get_sprite(win, BG);
	win->map->collect_sprite[0] = get_sprite(win, COIN_1);
	win->map->collect_sprite[1] = get_sprite(win, COIN_2);
	win->map->collect_sprite[2] = get_sprite(win, COIN_3);
	win->map->collect_sprite[3] = get_sprite(win, COIN_4);
	win->map->collect_sprite[4] = get_sprite(win, COIN_5);
	win->map->collect_sprite[5] = get_sprite(win, COIN_6);
	win->map->exit_sprite = get_sprite(win, EXIT);
	win->map->hud_sprite = get_sprite(win, UI);
	win->map->monster_sprite[0] = get_sprite(win, PATROL_1);
	win->map->monster_sprite[1] = get_sprite(win, PATROL_2);
	parse_map(win->map, map_path);
}

void	_init_data_(t_win *win, char *map_path)
{
	win->mlx = mlx_init();
	win->player = malloc(sizeof(t_player));
	win->player->hb = malloc(sizeof(t_hitbox));
	win->map = malloc (sizeof(t_map));
	win->is_lost = 0;
	win->is_win = 0;
	win->screen[0] = get_sprite(win, WIN_SCREEN);
	win->screen[1] = get_sprite(win, LOSE_SCREEN);
	if (!(win->player) || !(win->player->hb) || !(win->map))
		ft_perror("Memory allocation error");
	_init_map_(win, map_path);
	_init_player_(win->player, win);
	win->win = mlx_new_window(win->mlx, (win->map->x - 1) * TILE_WIDTH,
			win->map->y * TILE_LENGTH, "so_long");
}
