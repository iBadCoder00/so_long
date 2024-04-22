/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavila- <adavila-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:54:49 by adavila-          #+#    #+#             */
/*   Updated: 2024/04/21 20:54:49 by adavila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include "so_long.h"
# include "error_messages.h"

/*Functions to set the coordinates for every element after error-checking*/
int		parse_collectibles(t_map *map);
void	set_point(t_point *point, int x, int y);
t_point	*new_point(int x, int y);

/*Error checking functions as well as ft_perror 
that terminates the program to avoid unnecessary computing*/
int		check_walls(t_map *map);
int		check_lines(t_map *map);
int		flood_fill(int x, int y, char **map, int *solved);
int		ft_perror(char *error_message);
int		parse_line(const char *line, t_map *map, int n_line);
int		solve_maze(t_map *map, char *buffer);

/*Utils*/
int		is_set(char c, char *set);
#endif
