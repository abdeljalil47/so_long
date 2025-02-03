/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:37:35 by abdsebba          #+#    #+#             */
/*   Updated: 2025/01/30 20:37:13 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*ft_str_extantion(char *str, int c)
{
	int	i;

	i = ft_strlen(str);
	--i;
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((char *)(str + i));
		i--;
	}
	if ((char)c == '\0')
		return ((char *)(str));
	return (NULL);
}

int	ft_strcmp(char *s1, char *s2)
{
	if (s1 == NULL)
		return (-1);
	while (*s1 == *s2 && *s1)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	ft_check_path(char *str)
{
	char	*s;

	s = ft_str_extantion(str, '.');
	if (ft_strcmp(s, ".ber") == 0)
		return (1);
	else
		return (0);
}

char	*get_map(char *str, int *i)
{
	char	*line;
	char	*tmp;
	char	*bup;
	int		fd;

	line = NULL;
	tmp = NULL;
	bup = NULL;
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		bup = tmp;
		tmp = ft_strjoin(bup, line);
		if (!tmp)
			return (free(bup), free(line), close(fd), NULL);
		free(line);
		line = get_next_line(fd);
		(*i)++;
		free(bup);
	}
	close(fd);
	return (tmp);
}

int	main(int ac, char *av[])
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	if (ac != 2)
		return (1);
	if (!ft_check_path(av[1]))
		return (error_print("Wrong PATH!\n"), 1);
	tmp = get_map(av[1], &i);
	if (!tmp)
		return (error_print("couldn't open the map\n"), 1);
	if (create_2d_array(tmp, i) == NULL)
		return (free(tmp), 1);
	free(tmp);
}
