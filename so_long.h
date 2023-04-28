/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 07:46:31 by Cutku             #+#    #+#             */
/*   Updated: 2023/04/28 17:33:15 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include "MLX42/include/MLX42/MLX42.h"

# define CHAR_SET "CEP10X"
# define W_INPUT "Wrong input, map can only have 'C''E''P''1''0' characters.\n"
# define PLAYER_ERR "PLAYER has to be 1.\n"
# define EXIT_ERR "EXIT has to be 1.\n"
# define COLLECT_ERR "Collectible has to be at least 1.\n"
# define WALL_ERR "Map is not surrounded by walls.\n"

typedef struct s_collect
{
	int					cord[2];
	mlx_image_t			*collectible;
	struct s_collect	*next;
}	t_collect;

typedef struct s_game
{
	char	**map;
	int		width;
	int		height;
	int		collectible;
	int		player;
	int		pl_pos[2];
	int		exit;
	int		enemy;
	mlx_image_t	*bg;
	mlx_image_t	*pl;
	mlx_image_t	*tree;
	mlx_t		*mlx;
	t_collect	*keys;
	t_collect	*enemys;
	t_queue		**enemy_front_road;
	t_queue		**enemy_rear_road;
}	t_game;

typedef struct s_queue
{
	int	data[2];
	struct s_queue *next;
}	t_queue;

typedef struct s_parent
{
	int	i;
	int	j;
}	t_parent;

int		open_file(char *map);
int		width_map(char *line);
void	free_char_dubleptr(char **ptr, int size);
void	create_map(t_game *map, int fd);
void	measure_map(t_game *map, int fd);
int		is_valid_chars(t_game *map);
void	is_valid_map(t_game *map, int i, int j);
void	error_message(char *str, t_game *map);
//Queues
void	enqueue(t_queue **front, t_queue **rear, int *data);
void	dequeue(t_queue **front);
int		bfs(t_game *map, t_queue **front, t_queue **rear, char last);
//BFS
void	printf_shortest(t_game *map, t_parent **parent, int row, int col, char last);
int	check_right(t_queue **front, t_queue **rear, t_parent **parent, int **visited, t_game *map, char last);
int	check_down(t_queue **front, t_queue **rear, t_parent **parent, int **visited, t_game *map, char last);
int	check_up(t_queue **front, t_queue **rear, t_parent **parent, int **visited, t_game *map, char last);
int	check_left(t_queue **front, t_queue **rear, t_parent **parent, int **visited, t_game *map, char last);

//IMAGES
mlx_image_t	*xpm_to_image(t_game *game, char *path);
void	put_images(t_game *game);
void	init_images(t_game *map);

void	add_collectible(t_collect **first, int i, int j);
void	remove_collectible(t_game *game, t_collect **first, int i, int j);
mlx_image_t	*which_collectible(t_collect **first, int i, int j);
int			player_movement(t_game *game, int i, int j);

#endif