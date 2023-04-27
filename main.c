/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 06:43:56 by Cutku             #+#    #+#             */
/*   Updated: 2023/04/27 10:53:53 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	moves(mlx_key_data_t k_data, void *param)
{
	t_game	*game;

	game = param;
	if (k_data.action == MLX_PRESS)
	{
		if (k_data.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);
		if (k_data.key == MLX_KEY_UP || k_data.key == MLX_KEY_W)
			if (player_movement(game, game->pl_pos[0] - 1, game->pl_pos[1]))
				game->pl->instances->y -= 64;
		if (k_data.key == MLX_KEY_DOWN || k_data.key == MLX_KEY_S)
			if (player_movement(game, game->pl_pos[0] + 1, game->pl_pos[1]))
				game->pl->instances->y += 64;
		if (k_data.key == MLX_KEY_LEFT || k_data.key == MLX_KEY_A)
			if (player_movement(game, game->pl_pos[0], game->pl_pos[1] - 1))
				game->pl->instances->x -= 64;
		if (k_data.key == MLX_KEY_RIGHT || k_data.key == MLX_KEY_D)
			if (player_movement(game, game->pl_pos[0], game->pl_pos[1] + 1))
				game->pl->instances->x += 64;
	}
}

int	player_movement(t_game *game, int i, int j)
{
	if (game->map[i][j] != '1')
	{
		if (game->map[i][j] == 'C')
		{
			game->collectible--;
			remove_collectible(game, i, j);
		}
		game->map[game->pl_pos[0]][game->pl_pos[1]] = 0;
		game->map[i][j] = 'P';
		game->pl_pos[0] = i;
		game->pl_pos[1] = j;
		return (1);
	}
	return (0);
}

void	init_images(t_game *map)
{
	t_collect	*temp;

	map->mlx = mlx_init(map->width * 64, map->height * 64, "so_long", 1);
	if (!map->mlx)
		return ;
	map->bg = xpm_to_image(map, "./images/bg.xpm42");
	map->pl = xpm_to_image(map, "./images/player.xpm42");
	map->tree = xpm_to_image(map, "./images/tree.xpm42");
	temp = map->keys;
	while (temp)
	{
		temp->collectible = xpm_to_image(map, "./images/key.xpm42");
		temp = temp->next;
	}
}

void	put_images(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->height)
	{
		j = -1;
		while (++j < game->width)
		{
			mlx_image_to_window(game->mlx, game->bg, j * 64, i * 64);
			if (game->map[i][j] == '1')
				mlx_image_to_window(game->mlx, game->tree, j * 64, i * 64);
			if (game->map[i][j] == 'C')
				mlx_image_to_window(game->mlx, which_collectible(game, i, j), j * 64, i * 64);
		}
	}
	mlx_image_to_window(game->mlx, game->pl, game->pl_pos[1] * 64, game->pl_pos[0] * 64);
}

int	main(int argc, char **argv)
{
	t_game	map;
	t_queue	*front;
	t_queue	*rear;
	int		i;
	int		j;
	int		fd;

	front = NULL;
	rear = NULL;
	map.keys = NULL;
	if (argc == 2)
	{
		fd = open_file(argv[1]);
		measure_map(&map, fd);
		fd = open_file(argv[1]);
		create_map(&map, fd);
		is_valid_chars(&map);
		bfs(&map, &front, &rear);
		put_images(&map);
		mlx_key_hook(map.mlx, &moves, &map);
		mlx_loop(map.mlx);
		mlx_terminate(map.mlx);
	}
	return (0);
}
