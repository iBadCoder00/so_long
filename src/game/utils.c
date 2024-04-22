/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavila- <adavila-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:30:36 by adavila-          #+#    #+#             */
/*   Updated: 2024/04/21 20:30:36 by adavila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int	is_set(char c, char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

void	put_img(t_win *new_win, void *img, int x, int y)
{
	mlx_put_image_to_window(new_win->mlx, new_win->win, img, x, y);
}

void	*get_sprite(t_win *win, char *sprite_path)
{
	int		i;
	void	*img;

	i = 100;
	img = mlx_xpm_file_to_image(win->mlx, sprite_path, &i, &i);
	return (img);
}
