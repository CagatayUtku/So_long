/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 07:46:31 by Cutku             #+#    #+#             */
/*   Updated: 2023/05/12 20:19:29 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "../libft/libft.h"
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include "../MLX42/include/MLX42/MLX42.h"

# define CHAR_SET "CEP10X"
# define W_INPUT "Wrong input, map can only have 'C''E''P''1''0' characters.\n"
# define PLAYER_ERR "PLAYER has to be 1.\n"
# define EXIT_NO "There has to be an exit in the game.\n"
# define COLLECT_ERR "Collectible has to be at least 1.\n"
# define WALL_ERR "Map is not surrounded by walls.\n"
# define ENEMY_ERR "There is no enemy in the game.\n"
# define EXIT_PATH "Exit is unreachable.\n"

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
	int			num_move;
	t_queue		*front;
	t_queue		*rear;
	mlx_image_t	*move;
	mlx_image_t	*score;
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

//Init_map
int			open_file(char *map);
int			width_map(char *line);
void		create_map(t_game *map, int fd);
void		measure_map(t_game *map, int fd);
//Error_checks
int			is_valid_chars(t_game *map);
void		is_valid_map(t_game *map, int i, int j);
void		error_message(char *str, t_game *map);
//BFS
int			bfs(t_game *map, int target[2]);
int			check_neighbors(t_game *map, int i, int j, int target[2]);
void		clean_bfs(t_game *game);
//Queues
void		enqueue(t_queue **front, t_queue **rear, int *data);
void		dequeue(t_queue **front);
//IMAGES
mlx_image_t	*xpm_to_image(t_game *game, char *path);
void		img_window(mlx_t *mlx, mlx_image_t	*img, int j, int i);
void		put_images(t_game *game);
void		init_images(t_game *map);
void		scoreboard(t_game *game);
//MOVES
void		key_loop(mlx_key_data_t k_data, void *param);
int			player_movement(t_game *game, int i, int j);
void		player_key_press(mlx_key_data_t k_data, t_game *game);
void		is_collectible(t_game *game, int i, int j);
void		is_exit(t_game *game, int i, int j);
//ENEMY
void		enemy_loop(void *param);
void		enemy_move(t_game *game, t_object *m_enemy, int cord[2]);
int			is_enemy(t_object *ptr, int i, int j);
void		final_animation(t_game *game);
void		enemy_image_change(t_game *game);
//OBJECTS
int			num_object(t_object *first);
void		add_object(t_object **first, int i, int j);
mlx_image_t	*which_object(t_object **first, int i, int j);
void		remove_object(t_game *game, t_object **first, int i, int j);
//FREE
void		free_all(t_game *game);
void		free_objects(t_game *game, t_object **obj);
void		free_int_dubleptr(int **ptr, int size);
void		free_char_dubleptr(char **ptr, int size);

#endif