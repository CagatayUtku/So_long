/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 06:43:56 by Cutku             #+#    #+#             */
/*   Updated: 2023/04/29 12:39:44 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	moves(mlx_key_data_t k_data, void *param)
{
	t_game	*game;

	game = param;
	if (k_data.action == MLX_PRESS || k_data.action == MLX_REPEAT)
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
			remove_collectible(game, &game->keys, i, j);
		}
		if (game->map[i][j] == 'X')
			mlx_close_window(game->mlx);
		game->map[game->pl_pos[0]][game->pl_pos[1]] = 0;
		game->map[i][j] = 'P';
		game->pl_pos[0] = i;
		game->pl_pos[1] = j;
		return (1);
	}
	return (0);
}

void	generic_loop(void *param)
{
	t_game *game;
	static int	time = 0;
	int		num;

	game = param;
	time++;
	if (time % 30 == 0)
	{
		bfs(game, &game->front, &game->rear, 'X');
		printf("%d - %d \n", game->enemys->cord[0], game->enemy_road[0]);
		printf("%d - %d \n", game->enemys->cord[1], game->enemy_road[1]);
		if (game->enemys->cord[0] != game->enemy_road[0])
		{
			if (game->enemys->cord[1] == game->pl_pos[1] && game->enemys->cord[0] == game->pl_pos[0])
				mlx_close_window(game->mlx);
			num =  game->enemy_road[0] - game->enemys->cord[0];
			which_collectible(&game->enemys, game->enemys->cord[0], game->enemys->cord[1])->instances->y += 64 * num;
			game->map[game->enemys->cord[0]][game->enemys->cord[1]] = '0';
			game->enemys->cord[1] = game->enemy_road[1];
			game->enemys->cord[0] = game->enemy_road[0];
			game->map[game->enemys->cord[0]][game->enemys->cord[1]] = 'X';
		}
		if (game->enemys->cord[1] != game->enemy_road[1])
		{
			if (game->enemys->cord[1] == game->pl_pos[1] && game->enemys->cord[0] == game->pl_pos[0])
				mlx_close_window(game->mlx);
			num = game->enemy_road[1] - game->enemys->cord[1];
			which_collectible(&game->enemys, game->enemys->cord[0], game->enemys->cord[1])->instances->x += 64 * num;
			game->map[game->enemys->cord[0]][game->enemys->cord[1]] = '0';
			game->enemys->cord[1] = game->enemy_road[1];
			game->enemys->cord[0] = game->enemy_road[0];
			game->map[game->enemys->cord[0]][game->enemys->cord[1]] = 'X';
		}
	}
}

int	main(int argc, char **argv)
{
	t_game	map;
	t_queue	*front;
	t_queue	*rear;
	int		fd;

	map.front = NULL;
	map.rear = NULL;
	map.keys = NULL;
	map.enemys = NULL;
	if (argc == 2)
	{
		fd = open_file(argv[1]);
		measure_map(&map, fd);
		fd = open_file(argv[1]);
		create_map(&map, fd);
		is_valid_chars(&map);
		bfs(&map, &map.front, &map.rear, 'E');
		init_images(&map);
		put_images(&map);
		mlx_key_hook(map.mlx, &moves, &map);
		mlx_loop_hook(map.mlx, &generic_loop, &map);
		mlx_loop(map.mlx);
		mlx_terminate(map.mlx);
	}
	return (0);
}
