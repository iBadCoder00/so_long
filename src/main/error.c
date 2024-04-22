/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavila- <adavila-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:29:30 by adavila-          #+#    #+#             */
/*   Updated: 2024/04/21 20:29:30 by adavila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_format(char *map_path)
{
	int	fd;
	int	length;

	length = ft_strlen(map_path);
	if (length == 0 || !map_path)
		ft_perror("Empty string as map!");
	if (length < 4)
		ft_perror("Invalid map format");
	if (ft_strncmp((map_path + length - 4), ".ber", 4) != 0)
		ft_perror("Invalid map format");
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		ft_perror("No such file");
	return (fd);
}

int	ft_perror(char *error_message)
{
	if (!error_message)
	{
		ft_printf("No error message was given!");
		return (0);
	}
	ft_printf("Error:\n%s\n", error_message);
	exit (1);
}
