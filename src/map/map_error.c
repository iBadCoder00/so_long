/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavila- <adavila-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:30:00 by adavila-          #+#    #+#             */
/*   Updated: 2024/04/21 20:30:00 by adavila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

/*Reads the whole line and if no parsing problems were found
return the length of the line*/
int	parse_line(const char *line, t_map *map, int n_line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!is_set(line[i], "01ECPM\n"))
			ft_perror(BAD_CHAR);
		if (line[i] == 'P')
		{
			map->n_starts += 1;
			set_point(&map->starting_point, i, n_line);
		}
		else if (line[i] == 'E')
		{
			map->n_exits += 1;
			set_point(&map->exit_point, i, n_line);
		}
		else if (line[i] == 'C')
			map->n_collectables += 1;
		i++;
	}
	if (map->n_exits > 1 || map->n_starts > 1)
		return (ft_perror(BAD_SPAWN));
	return (i);
}

/*Read through the perimeter of the map and return 
with an exit message if walls were not properly closed*/
int	check_walls(t_map *map)
{
	int	i;

	i = 0;
	if (map->x <= 2 || map->y <= 2)
		return (ft_perror(NO_WALK));
	if (map->n_exits == 0 || map->n_starts == 0)
		return (ft_perror(BAD_SPAWN));
	else if (map->n_collectables == 0)
		return (ft_perror(NULL_COLLECTS));
	while (i < map->x - 1)
	{
		if (map->map_table[0][i] != '1' || map->map_table[map->y - 1][i] != '1')
			return (ft_perror(BAD_CLOSE));
		i++;
	}
	i = 0;
	while (i < map->y)
	{
		if (map->map_table[i][0] != '1' || map->map_table[i][map->x - 1] != '1')
			return (ft_perror(BAD_CLOSE));
		i++;
	}
	return (1);
}

/*Iterate over every line and call parse_line() 
to check for duplicate entries/exits and minimum number of collectibles*/
int	check_lines(t_map *map)
{
	int	n_lines;
	int	l_current_length;
	int	l_prev_length;

	n_lines = 0;
	l_current_length = 0;
	l_prev_length = 0;
	while (map->map_table[n_lines])
	{
		l_current_length = parse_line(map->map_table[n_lines], map, n_lines);
		if (n_lines > 0 && l_prev_length != l_current_length)
			return (ft_perror(BAD_LINE));
		l_prev_length = l_current_length;
		n_lines++;
	}
	if (n_lines == l_prev_length)
		return (ft_perror(BAD_GEOMETRY));
	map->x = l_prev_length;
	map->y = n_lines;
	return (1);
}

/*Parse and check if the given map is a valid set for the game*/
int	check_elements(t_map *map, char *buffer)
{
	map->map_table = ft_split(buffer, '\n');
	check_lines(map);
	check_walls(map);
	solve_maze(map, buffer);
	parse_collectibles(map);
	return (1);
}
