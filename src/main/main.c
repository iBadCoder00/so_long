/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavila- <adavila-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:29:45 by adavila-          #+#    #+#             */
/*   Updated: 2024/04/21 20:29:45 by adavila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

long long	millitimestamp(void)
{
	struct timeval	timeval;
	long long		microtime;

	gettimeofday(&timeval, NULL);
	microtime = timeval.tv_sec * 1000LL + timeval.tv_usec / 1000;
	return (microtime);
}

int	update(t_win *win)
{
	static long long	time = 0;
	long long			time_diff;

	time_diff = millitimestamp();
	if (win->is_lost || win->is_win)
		game_end(win);
	else if (time_diff - time > 10)
	{
		mlx_clear_window(win->mlx, win->win);
		draw_scene(win);
		draw_player(win);
		draw_ui(win);
		time = millitimestamp();
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_win	new_win;

	if (argc != 2)
		exit (1);
	_init_data_(&new_win, argv[1]);
	_init_hooks(&new_win);
	mlx_loop_hook(new_win.mlx, update, &new_win);
	mlx_loop(new_win.mlx);
}
