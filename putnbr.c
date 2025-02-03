/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:38:28 by abdsebba          #+#    #+#             */
/*   Updated: 2025/02/02 15:42:20 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_putnbr(int nb)
{
	char	out;

	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (nb == 0)
		write(1, "0", 1);
	else if (nb < 0)
	{
		write(1, "-", 1);
		nb *= -1;
		ft_putnbr(nb);
	}
	else
	{
		if (nb / 10 != 0)
			ft_putnbr(nb / 10);
		out = nb % 10 + 48;
		write(1, &out, 1);
	}
}

void	handle_key(int keycode)
{
	ft_putnbr(keycode);
	write(1, "\n", 1);
}

char	*ft_copy_map(t_data *game)
{
	char	*ttmp;
	char	*bup;
	int		y;

	y = 0;
	ttmp = NULL;
	while (game->map->map[y])
	{
		bup = ttmp;
		ttmp = ft_strjoin1(bup, game->map->map[y]);
		if (!ttmp)
			return (free(bup), NULL);
		free(bup);
		y++;
	}
	return (ttmp);
}

int	load_textures(t_data *game, void *mlx)
{
	game->wall = mlx_xpm_file_to_image(mlx, "textures/wall.xpm",
			&game->width, &game->height);
	game->player1.player_left = mlx_xpm_file_to_image(mlx,
			"textures/walk.xpm", &game->width, &game->height);
	game->player1.player_right = mlx_xpm_file_to_image(mlx,
			"textures/walk1.xpm", &game->width, &game->height);
	game->exit = mlx_xpm_file_to_image(mlx,
			"textures/exit.xpm", &game->width, &game->height);
	game->collectible = mlx_xpm_file_to_image(mlx,
			"textures/collectible.xpm", &game->width, &game->height);
	if (!game->wall || !game->player1.player_left || !game->player1.player_right
		|| !game->exit || !game->collectible)
		return (0);
	return (1);
}

void	cleanup_resources(t_data *game)
{
	if (game->mlx)
	{
		if (game->wall)
			mlx_destroy_image(game->mlx, game->wall);
		if (game->player1.player_left)
			mlx_destroy_image(game->mlx, game->player1.player_left);
		if (game->player1.player_right)
			mlx_destroy_image(game->mlx, game->player1.player_right);
		if (game->exit)
			mlx_destroy_image(game->mlx, game->exit);
		if (game->collectible)
			mlx_destroy_image(game->mlx, game->collectible);
		free(game->mlx);
	}
}
