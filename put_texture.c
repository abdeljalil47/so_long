/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:38:25 by abdsebba          #+#    #+#             */
/*   Updated: 2025/02/02 16:04:22 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	make_background(int width, int height, t_data *game)
{
	int	orange;
	int	x;
	int	y;

	y = 0;
	orange = 0xFFFFFF;
	while (y++ < height)
	{
		x = 0;
		while (x++ < width)
			mlx_pixel_put(game->mlx, game->mlx_screen, x * 50, y * 50, orange);
	}
}

void	elements(int m, int i, t_data *game, char **map)
{
	if (map[i][m] == '1')
		mlx_put_image_to_window(game->mlx, game->mlx_screen,
			game->wall, m * 50, i * 50);
	else if (map[i][m] == 'P')
		ft_s_position(map, game, game->mlx_screen, game->mlx);
	else if (map[i][m] == 'E')
		mlx_put_image_to_window(game->mlx, game->mlx_screen,
			game->exit, m * 50, i * 50);
	else if (map[i][m] == 'C')
		mlx_put_image_to_window(game->mlx, game->mlx_screen,
			game->collectible, 7 + m * 50, 10 + i * 50);
}

int	ft_put_texture(char **map, void *mlx, t_data *game)
{
	int	i;
	int	m;

	i = 0;
	m = 0;
	if (!load_textures(game, mlx))
		return (error_print("Error in xpm image!\n"), 0);
	while (map[i])
	{
		m = 0;
		while (map[i][m])
		{
			elements(m, i, game, map);
			m++;
		}
		i++;
	}
	return (1);
}

void	finish_game(t_data *game_data)
{
	write(1, "\033[32mYou Won!\n\033[0m", 15);
	mlx_destroy_window(game_data->mlx, game_data->mlx_screen);
	cleanup_resources(game_data);
	ft_free(game_data->map->map, game_data, game_data->map);
	exit(0);
}

int	finish(int prev_x, int prev_y, t_data *game_data)
{
	if ((game_data->map->map[prev_y][prev_x] == 'E')
		&& (game_data->check_coll == game_data->coll))
	{
		game_data->move++;
		handle_key(game_data->move);
		return (1);
	}
	else
		return (0);
}
