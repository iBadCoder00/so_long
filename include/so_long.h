/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavila- <adavila-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:29:36 by adavila-          #+#    #+#             */
/*   Updated: 2024/04/21 20:29:36 by adavila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include <X11/keysym.h>
# include "mlx.h"
# include "libft.h"
# include "path.h"

//Endgame settings
# define END_WIDTH 450
# define END_LENGTH 100

//Player settings
# define P_WIDTH 16
# define P_LENGTH 28

//Patrol settings
# define M_WIDTH 24
# define M_LENGTH 26
# define M_XOFFSET 4
# define M_YOFFSET 6

//Map & static elements settings
# define TILE_WIDTH 32
# define TILE_LENGTH 32
# define COLLECT_WIDTH 16
# define COLLECT_LENGTH 16
# define X_OFFSET 10
# define Y_OFFSET 10
# define BUFF_SIZE 10001

//Physics
# define GRAVITY -500
# define GRAVITY_DT 0.01666
# define V_INIT 340
# define V_DT 0.01666
# define X_DX 1

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_map
{
	t_point	starting_point;
	t_point	exit_point;
	t_list	*monsters;
	int		x;
	int		y;
	int		n_starts;
	int		n_exits;
	int		n_collectables;
	char	**map_table;
	void	*wall_sprite;
	void	*bg;
	void	*collect_sprite[6];
	void	*monster_sprite[2];
	void	*exit_sprite;
	void	*hud_sprite;
}	t_map;

typedef struct s_hitbox
{
	int	left;
	int	top;
	int	right;
	int	bottom;
}	t_hitbox;

typedef struct s_player
{
	int			x;
	int			y;
	t_hitbox	*hb;
	int			gravity;
	int			movements;
	int			is_moving;
	int			is_airborne;
	int			y_velocity;
	int			x_direction;
	void		*sprite;
	void		*run_rsprite[8];
	void		*run_lsprite[8];
	void		*idle_sprite[2];
	void		*airborne_sprite[2];
}	t_player;

typedef struct s_win
{
	void		*mlx;
	void		*win;
	void		*screen[2];
	int			is_win;
	int			is_lost;
	t_map		*map;
	t_player	*player;
}	t_win;

//Startup functions and helpers
void	_init_data_(t_win *win, char *map_path);
int		check_elements(t_map *map, char *buffer);
void	game_end(t_win *win);

//Error handling
int		ft_perror(char *error_message);
int		check_format(char *map_path);

//Player functionality
void	update_player(t_win *win);

//Physics functionality
int		is_hitbox(t_player *player, char **map, char hit_char);
void	aabb_collision_x(t_player *player, char **map);
void	aabb_collision_y(t_player *player, char **map);
void	is_grounded(t_player *player, char **map);

//Wrappers & drawing functionality
void	draw_scene(t_win *win);
void	draw_player(t_win *win);
void	draw_ui(t_win *win);
void	render_map(t_win *win);
void	render_patrol(t_win *win);
void	render_exit(t_win *win);

//Hooks
int		key_press(int key, t_win *win);
int		key_release(int key, t_win *win);
int		close_window(t_win *win);
void	_init_hooks(t_win *win);

//Utils
void	put_img(t_win *new_win, void *img, int x, int y);
void	*get_sprite(t_win *win, char *sprite_path);
#endif