/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:37:43 by abdsebba          #+#    #+#             */
/*   Updated: 2025/01/26 13:24:32 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_check_map1_bup(char **map)
{
	int	i;
	int	y;
	int	f_p;
	int	f_e;

	i = 0;
	f_e = 0;
	f_p = 0;
	while (map[i])
	{
		y = 0;
		while (map[i][y])
		{
			if (map[i][y] == 'E')
				f_e++;
			else if (map[i][y] == 'P')
				f_p++;
			y++;
		}
		i++;
	}
	if (f_e != 1 || f_p != 1)
		return (0);
	return (1);
}

char	*ft_strlast(char *str, int c)
{
	int	i;

	i = ft_strlen(str);
	--i;
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((char *)(str + i));
		break ;
		i--;
	}
	if ((char)c == '\0')
		return ((char *)(str));
	return (NULL);
}

int	ft_check_size(char **map, int i, int x, int size)
{
	x = 0;
	size = 0;
	while (map[x])
		x++;
	if (x != i)
		return (0);
	size = ft_strlen(map[0]);
	if (size == x)
		return (0);
	x = 0;
	while (map[x])
	{
		size = 0;
		while (map[x][size])
		{
			if (map[x][size] != '0' && map[x][size] != '1'
				&& map[x][size] != 'C' && map[x][size] != 'E'
				&& map[x][size] != 'P')
				return (0);
			size++;
		}
		x++;
	}
	return (1);
}

int	ft_check_walls(char **map, int i)
{
	int	y;
	int	x;
	int	size;

	y = 0;
	x = 0;
	size = 0;
	while (map[0][y])
	{
		if (map[0][y] != '1')
			return (0);
		y++;
	}
	y = 0;
	if (!ft_check_size(map, i, x, size))
		return (0);
	while (map[i - 1][y])
	{
		if (map[i - 1][y] != '1')
			return (0);
		y++;
	}
	if (!check_walls(map, i))
		return (0);
	return (1);
}

int	check_walls(char **map, int i)
{
	int	y;

	y = 0;
	while (i > 0 && map[i - 1][y])
	{
		if (map[i - 1][y] != '1')
			return (0);
		i--;
	}
	y = 0;
	while (map[y])
	{
		if (ft_strlast(map[y], '1') == NULL)
			return (0);
		y++;
	}
	return (1);
}
