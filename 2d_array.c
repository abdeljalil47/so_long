/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:37:40 by abdsebba          #+#    #+#             */
/*   Updated: 2025/02/02 15:51:43 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_long	*create_2d_array(char *tmp, int i)
{
	t_long	*game_map;
	t_data	*game;

	game_map = (t_long *)malloc(sizeof(t_long));
	if (game_map == NULL)
		return ((free(game_map)), NULL);
	game = malloc(sizeof(t_data));
	if (game == NULL)
		return ((free(game_map), free(game)), NULL);
	game->map = game_map;
	game_map->map = ft_split(tmp, '\n');
	if (game_map->map == NULL)
		return ((free(game_map), free(game)), NULL);
	// if (!ft_check_map1_bup(game_map->map) || !ft_check_walls(game_map->map, i)
	// 	|| !ft_are_lineequal(game_map->map))
	// 	return ((ft_free(game_map->map, game, game_map),
	// 			error_print("Map not valide\n")), NULL);
	game_map->width = count_map(game_map->map);
	game_map->height = i;
	if (!ft_handle_map(game))
		return ((ft_free(game_map->map, game, game_map)), NULL);
	if (!create_window(game_map, game_map->width, game_map->height, game))
		return (ft_free(game_map->map, game, game_map), NULL);
	ft_free(game_map->map, game, game_map);
	return (game_map);
}

void	count(char **map, t_play *player)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
			{
				player->position_x = x;
				player->position_y = y;
			}
			x++;
		}
		y++;
	}
}

void	ft_s_position(char **map, t_data *game, void *mlx_screen, void *mlx)
{
	count(map, &game->player1);
	if (game->player1.flag == 1)
		mlx_put_image_to_window(mlx, mlx_screen, game->player1.player_left,
			5 + game->player1.position_x * 50, game->player1.position_y * 50);
	else
		mlx_put_image_to_window(mlx, mlx_screen, game->player1.player_right,
			game->player1.position_x * 50, game->player1.position_y * 50);
}

int	count_map(char **map)
{
	int	m;

	m = 0;
	if (map == NULL || *map == NULL)
		return (0);
	while (map[0][m])
		m++;
	return (m);
}

int	close_window(t_data *param)
{
	write(2, "\033[31mClosing the window...\n\033[0m", 30);
	mlx_destroy_window(param->mlx, param->mlx_screen);
	cleanup_resources(param);
	ft_free(param->map->map, param, param->map);
	write(2, "\033[31mWindow closed!\n\033[0m", 22);
	exit(0);
	return (1);
}
