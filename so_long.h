/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:38:38 by abdsebba          #+#    #+#             */
/*   Updated: 2025/02/02 15:41:51 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct so_long
{
	char	**map;
	int		width;
	int		height;
}	t_long;

typedef struct player
{
	int		position_x;
	int		position_y;
	void	*player;
	void	*player_left;
	void	*player_right;
	int		flag;
}	t_play;

typedef struct s_data
{
	void	*mlx;
	void	*mlx_screen;
	void	*img;
	void	*collectible;
	void	*wall;
	void	*exit;
	t_play	player1;
	t_long	*map;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		coll;
	int		check_coll;
	int		width;
	int		height;
	int		move;
}	t_data;

t_long	*create_2d_array(char *tmp, int i);
void	count(char **map, t_play *player);
void	ft_s_position(char **map, t_data *game, void *mlx_screen, void *mlx);
int		count_map(char **map);
int		close_window(t_data *param);

int		ft_check_map1_bup(char **map);
char	*ft_strlast(char *str, int c);
int		ft_check_walls(char **map, int i);

int		create_window(t_long *game_map, int width, int height, t_data *game);
void	move_player(t_data *game_data, int delta_y, int delta_x);
void	left(int keycode, t_data *game_data, int prev_y, int prev_x);
void	ft_move_player(int keycode, t_data *game_data, int prev_y, int prev_x);
int		key_hook(int keycode, void *param);

int		error_print(char *str);
char	**ft_split(const char *s, char c);

size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(const char *s, unsigned int start, size_t len);

char	*get_next_line(int fd);

char	*ft_strjoin1(char *s1, char *s2);
int		count_coll(char **map1);
bool	flood_fill_exit(char **map, int x, int y, t_data *game);
int		flood_fill_collectibles(char **map, int x, int y, t_data *game);
int		ft_handle_map(t_data *game);

void	make_background(int width, int height, t_data *game);
void	elements(int m, int i, t_data *game, char **map);
int		ft_put_texture(char **map, void *mlx, t_data *game);
void	finish_game(t_data *game_data);

void	ft_putnbr(int nb);
void	handle_key(int keycode);
char	*ft_copy_map(t_data *game);

char	*ft_str(char *str, int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_check_path(char *str);
int		load_textures(t_data *game, void *mlx);
char	*get_map(char *str, int *i);
int		check_walls(char **map, int i);
int		ft_are_lineequal(char **tmp);
int		ft_cont_line(char *tmp);
int		finish(int prev_x, int prev_y, t_data *game_data);

void	ft_free(char **map, t_data *game, t_long *game_map);
void	ft_free1(char*tmp, char **map, char **map1);
void	cleanup_resources(t_data *game);

#endif 