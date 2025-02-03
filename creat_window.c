/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:37:45 by abdsebba          #+#    #+#             */
/*   Updated: 2025/02/02 15:32:46 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	create_window(t_long *game_map, int width, int height, t_data *game)
{
	game->check_coll = 0;
	game->move = 0;
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		return ((write(1, "MinilibX initialization failed\n", 34)), 0);
	game->mlx_screen = mlx_new_window(game->mlx, width * 50,
			height * 50, "so_long");
	if (!game->mlx_screen)
		return ((write(1, "MinilibX initialization failed\n", 26)), 0);
	if (!ft_put_texture(game_map->map, game->mlx, game))
		return (close_window(game), 0);
	make_background(width, height, game);
	mlx_hook(game->mlx_screen, 2, 0, &key_hook, game);
	mlx_hook(game->mlx_screen, 17, 0, &close_window, game);
	mlx_loop(game->mlx);
	return (1);
}

void	move_player(t_data *game_data, int delta_y, int delta_x)
{
	int	prev_y;
	int	prev_x;

	if (delta_x == 1)
		game_data->player1.flag = 0;
	prev_y = game_data->player1.position_y;
	prev_x = game_data->player1.position_x;
	game_data->player1.position_y += delta_y;
	game_data->player1.position_x += delta_x;
	game_data->map->map[prev_y][prev_x] = '0';
	game_data->map->map[game_data->player1.position_y]
	[game_data->player1.position_x] = 'P';
	mlx_clear_window(game_data->mlx, game_data->mlx_screen);
	make_background(game_data->map->width, game_data->map->height, game_data);
	ft_put_texture(game_data->map->map, game_data->mlx, game_data);
	game_data->move++;
	handle_key(game_data->move);
}

void	left(int keycode, t_data *game_data, int prev_y, int prev_x)
{
	if (keycode == 123 || keycode == 0)
	{
		if (finish(prev_x - 1, prev_y, game_data))
			return (finish_game(game_data));
		if (game_data->map->map[prev_y][prev_x - 1] != '1'
			&& game_data->map->map[prev_y][prev_x - 1] != 'E')
		{
			if (game_data->map->map[prev_y][prev_x - 1] == 'C')
				game_data->check_coll += 1;
			game_data->player1.flag = 1;
			move_player(game_data, 0, -1);
		}
	}
	else if (keycode == 126 || keycode == 13)
	{
		if (finish(prev_x, prev_y - 1, game_data))
			return (finish_game(game_data));
		if (game_data->map->map[prev_y - 1][prev_x] != '1'
			&& game_data->map->map[prev_y - 1][prev_x] != 'E')
		{
			if (game_data->map->map[prev_y - 1][prev_x] == 'C')
				game_data->check_coll += 1;
			move_player(game_data, -1, 0);
		}
	}
}

void	ft_move_player(int keycode, t_data *game_data, int prev_y, int prev_x)
{
	left(keycode, game_data, prev_y, prev_x);
	if (keycode == 125 || keycode == 1)
	{
		if (finish(prev_x, prev_y + 1, game_data))
			return (finish_game(game_data));
		if (game_data->map->map[prev_y + 1][prev_x] != '1'
			&& game_data->map->map[prev_y + 1][prev_x] != 'E')
		{
			if (game_data->map->map[prev_y + 1][prev_x] == 'C')
				game_data->check_coll += 1;
			move_player(game_data, 1, 0);
		}
	}
	else if (keycode == 124 || keycode == 2)
	{
		if (finish(prev_x + 1, prev_y, game_data))
			return (finish_game(game_data));
		if (game_data->map->map[prev_y][prev_x + 1] != '1'
			&& game_data->map->map[prev_y][prev_x + 1] != 'E')
		{
			if (game_data->map->map[prev_y][prev_x + 1] == 'C')
				game_data->check_coll += 1;
			move_player(game_data, 0, 1);
		}
	}
}

int	key_hook(int keycode, void *param)
{
	t_data	*game_data;
	int		prev_x;
	int		prev_y;

	game_data = (t_data *)param;
	prev_x = game_data->player1.position_x;
	prev_y = game_data->player1.position_y;
	if (keycode == 53)
		return ((close_window(game_data)), 1);
	ft_move_player(keycode, game_data, prev_y, prev_x);
	return (0);
}
