/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavila- <adavila-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:30:03 by adavila-          #+#    #+#             */
/*   Updated: 2024/04/21 20:30:03 by adavila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

/*Uses the given buffer to create a copy of the map and tries to solve it 
with flood_fill(),if a solution is not reachable, return with a error message*/
int	solve_maze(t_map *map, char *buffer)
{
	int		i;
	int		solved[2];
	char	**temp_map;

	temp_map = ft_split(buffer, '\n');
	if (!temp_map)
		ft_perror("An error ocurred while allocating the test map!");
	solved[0] = 0;
	solved[1] = map->n_collectables;
	flood_fill(map->starting_point.y, map->starting_point.x, temp_map, solved);
	i = 0;
	while (temp_map[i])
		free(temp_map[i++]);
	free(temp_map);
	if (solved[0] == 0 || solved[1] != 0)
		return (ft_perror("Map is not solvable"));
	return (1);
}

/*Algorithm that tries to find a solution to the given map.*/
int	flood_fill(int x, int y, char **map, int *solved)
{
	if (solved[0] && solved[1] == 0)
		return (1);
	if (x < 0 || y < 0 || map[x][y] == '1' || map[x][y] == 'x'
		|| map[x][y] == 'M')
		return (0);
	if (map[x][y] == 'C')
		solved[1] -= 1;
	if (map[x][y] == 'E')
		solved[0] = 1;
	map[x][y] = 'x';
	flood_fill(x, y + 1, map, solved);
	flood_fill(x + 1, y, map, solved);
	flood_fill(x, y - 1, map, solved);
	flood_fill(x - 1, y, map, solved);
	return (0);
}

t_point	*new_point(int x, int y)
{
	t_point	*new_point;

	new_point = malloc(sizeof(t_point));
	if (!new_point)
		ft_perror("An error ocurred while creating a point!");
	new_point->x = x;
	new_point->y = y;
	return (new_point);
}

/*Iterates over the map and if the 'C' character is found,
it creates a new node and adds it to the linked list
collectibles in the t_map struct.The created node contains 
as content a variable of type t_point with the coordinates of the function*/
int	parse_collectibles(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map_table[i])
	{
		j = 0;
		while (map->map_table[i][j])
		{
			if (map->map_table[i][j] == 'M')
				ft_lstadd_back(&map->monsters, ft_lstnew(new_point(j, i)));
			j++;
		}
		i++;
	}
	return (1);
}

void	set_point(t_point *point, int x, int y)
{
	point->x = x;
	point->y = y;
}
