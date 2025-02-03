/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:37:48 by abdsebba          #+#    #+#             */
/*   Updated: 2025/02/02 16:03:41 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	error_print(char *str)
{
	int	size;

	write(2, "\033[31mError:\n\033[0m", 15);
	if (str != NULL)
	{
		size = ft_strlen(str);
		write(2, "\033[31m", 5);
		write(2, str, size);
		write(2, "\033[0m", 4);
	}
	return (1);
}

int	ft_cont_line(char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i] != '\n' && tmp[i])
		i++;
	return (i);
}

int	ft_are_lineequal(char **tmp)
{
	int	i;
	int	size;
	int	count;

	i = 0;
	count = 0;
	size = ft_cont_line(tmp[0]);
	while (tmp[i])
	{
		count = ft_cont_line(tmp[i]);
		if (size != count)
			return (0);
		i++;
	}
	return (1);
}

void	ft_free(char **map, t_data *game, t_long *game_map)
{
	int	i;

	i = 0;
	if (map)
	{
		while (map[i])
			free(map[i++]);
		free(map);
	}
	if (game)
		free(game);
	if (game_map)
		free(game_map);
}

void	ft_free1(char *tmp, char **map, char **map1)
{
	int	i;

	i = 0;
	if (map)
	{
		while (map[i])
			free(map[i++]);
		free(map);
	}
	i = 0;
	if (map1)
	{
		while (map1[i])
			free(map1[i++]);
		free(map1);
	}
	free(tmp);
}
