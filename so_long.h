/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 07:46:31 by Cutku             #+#    #+#             */
/*   Updated: 2023/05/09 02:10:43 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include <errno.h>
# include <unistd.h>
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
# define ENEMY_ERR "There is no enemy in the game.\n"

typedef struct s_object
{
	int				cord[2];
	mlx_image_t		*image;
	struct s_object	*next;
}	t_object;

typedef struct s_queue
{
	int				data[2];
	struct s_queue	*next;
}	t_queue;

typedef struct s_game
{
	char		**map;
	int			width;
	int			height;
	int			state;
	int			enemy_road[2];
	int			**visited;
	t_queue		*front;
	t_queue		*rear;
	mlx_image_t	*bg;
	mlx_image_t	*wall;
	mlx_image_t	*success;
	mlx_image_t	*fail;
	mlx_t		*mlx;
	t_object	*collect;
	t_object	*enemys;
	t_object	*player;
	t_object	*exit;
}	t_game;

int			open_file(char *map);
int			width_map(char *line);
void		free_char_dubleptr(char **ptr, int size);
void		create_map(t_game *map, int fd);
void		measure_map(t_game *map, int fd);
int			is_valid_chars(t_game *map);
void		is_valid_map(t_game *map, int i, int j);
void		error_message(char *str, t_game *map);
//Queues
void		enqueue(t_queue **front, t_queue **rear, int *data);
void		dequeue(t_queue **front);
//BFS
int			bfs(t_game *map, int target[2]);
int			check_neighbors(t_game *map, int i, int j, int target[2]);
void		clean_bfs(t_game *game);
void		free_int_dubleptr(int **ptr, int size);

//IMAGES
mlx_image_t	*xpm_to_image(t_game *game, char *path);
void		img_window(mlx_t *mlx, mlx_image_t	*img, int j, int i);
void		put_images(t_game *game);
void		init_images(t_game *map);

void		enemy_move(t_game *game, t_object *m_enemy, int cord[2]);
int			num_object(t_object *first);
void		add_object(t_object **first, int i, int j);
void		remove_object(t_game *game, t_object **first, int i, int j);
mlx_image_t	*which_object(t_object **first, int i, int j);
int			player_movement(t_game *game, int i, int j);
int			is_enemy(t_object *ptr, int i, int j);
void		free_all(t_game *game);

#endif