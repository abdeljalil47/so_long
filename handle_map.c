/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:38:14 by abdsebba          #+#    #+#             */
/*   Updated: 2025/02/02 15:34:24 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*ft_strjoin1(char *s1, char *s2)
{
	char	*array;
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	array = (char *)malloc((len1 + len2 + 2));
	if (array == NULL)
		return (NULL);
	ft_strlcpy(array, s1, len1 + 1);
	array[len1] = '\n';
	ft_strlcpy(array + len1 + 1, s2, len2 + 1);
	return (array);
}

int	count_coll(char **map1)
{
	int	y;
	int	x;
	int	count;

	y = 0;
	x = 0;
	count = 0;
	while (map1[y])
	{
		x = 0;
		while (map1[y][x])
		{
			if (map1[y][x] == 'C')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

bool	flood_fill_exit(char **map, int x, int y, t_data *game)
{
	bool	reached;

	if (x <= 0 || y <= 0 || x >= game->map->width || y >= game->map->height
		|| map[y][x] == '1' || map[y][x] == 'X')
		return (false);
	if (map[y][x] == 'E')
		return (true);
	map[y][x] = 'X';
	reached = (flood_fill_exit(map, x + 1, y, game)
			|| flood_fill_exit(map, x - 1, y, game)
			|| flood_fill_exit(map, x, y + 1, game)
			|| flood_fill_exit(map, x, y - 1, game));
	return (reached);
}

int	flood_fill_collectibles(char **map, int x, int y, t_data *game)
{
	int	reached;

	reached = 0;
	if (x <= 0 || y <= 0 || x >= game->map->width || y >= game->map->height
		|| map[y][x] == '1' || map[y][x] == 'E' || map[y][x] == 'X')
		return (0);
	if (map[y][x] == 'C')
		reached++;
	map[y][x] = 'X';
	reached += flood_fill_collectibles(map, x + 1, y, game);
	reached += flood_fill_collectibles(map, x - 1, y, game);
	reached += flood_fill_collectibles(map, x, y + 1, game);
	reached += flood_fill_collectibles(map, x, y - 1, game);
	return (reached);
}

int	ft_handle_map(t_data *game)
{
	int		size;
	char	*ttmp;
	char	**mmp;
	char	**mmp1;

	ttmp = ft_copy_map(game);
	mmp = ft_split(ttmp, '\n');
	if (!mmp)
		return (free(ttmp), 0);
	mmp1 = ft_split(ttmp, '\n');
	if (!mmp1)
		return (ft_free(mmp, NULL, NULL), free(ttmp), 0);
	game->coll = count_coll(mmp);
	count(mmp, &game->player1);
	size = flood_fill_collectibles(mmp, game->player1.position_x,
			game->player1.position_y, game);
	if (flood_fill_exit(mmp1, game->player1.position_x,
			game->player1.position_y, game) == false)
		return ((ft_free1(ttmp, mmp1, mmp),
				error_print("Error in map: Can't reach to Exit!\n")), 0);
	if (size != game->coll || game->coll == 0)
		return (ft_free1(ttmp, mmp1, mmp),
			error_print("Error in map: Can't reach to Collectibles\n"), 0);
	ft_free1(ttmp, mmp1, mmp);
	return (1);
}
