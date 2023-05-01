/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 06:43:56 by Cutku             #+#    #+#             */
/*   Updated: 2023/05/01 23:12:34 by Cutku            ###   ########.fr       */
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
				game->pl->instances->y -= 80;
		if (k_data.key == MLX_KEY_DOWN || k_data.key == MLX_KEY_S)
			if (player_movement(game, game->pl_pos[0] + 1, game->pl_pos[1]))
				game->pl->instances->y += 80;
		if (k_data.key == MLX_KEY_LEFT || k_data.key == MLX_KEY_A)
			if (player_movement(game, game->pl_pos[0], game->pl_pos[1] - 1))
				game->pl->instances->x -= 80;
		if (k_data.key == MLX_KEY_RIGHT || k_data.key == MLX_KEY_D)
			if (player_movement(game, game->pl_pos[0], game->pl_pos[1] + 1))
				game->pl->instances->x += 80;
	}
}

int	player_movement(t_game *game, int i, int j)
{
	if (game->map[i][j] != '1')
	{
		if (!is_enemy(game->enemys, i, j))
		{
			if (game->map[i][j] == 'C')
			{
				game->num_collect--;
				remove_object(game, &game->collect, i, j);
			}
			game->map[game->pl_pos[0]][game->pl_pos[1]] = '0';
			game->map[i][j] = 'P';
			game->pl_pos[0] = i;
			game->pl_pos[1] = j;
			return (1);
		}
		mlx_close_window(game->mlx);
	}
	return (0);
}
int	is_enemy(t_object *ptr, int i, int j)
{
	while (ptr)
	{
		if (ptr->cord[0] == i && ptr->cord[1] == j)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

void	generic_loop(void *param)
{
	t_game *game;
	t_object	*m_enemy;
	static int	time = 0;
	int		num;

	game = param;
	time++;
	m_enemy = game->enemys;
	if (time % 30 == 0)
	{
		while (m_enemy)
		{
			bfs(game, m_enemy->cord);
			if (m_enemy->cord[0] != game->enemy_road[0])
			{
				if (!is_enemy(game->enemys, game->enemy_road[0], game->enemy_road[1]))
				{
					num =  game->enemy_road[0] - m_enemy->cord[0];
					m_enemy->image->instances->y += (80 * num);
					m_enemy->cord[0] = game->enemy_road[0];
					if (m_enemy->cord[1] == game->pl_pos[1] && m_enemy->cord[0] == game->pl_pos[0])
						mlx_close_window(game->mlx);
				}
			}
			if (m_enemy->cord[1] != game->enemy_road[1])
			{
				if (!is_enemy(game->enemys, game->enemy_road[0], game->enemy_road[1]))
				{
					num = game->enemy_road[1] - m_enemy->cord[1];
					m_enemy->image->instances->x += (80 * num);
					m_enemy->cord[1] = game->enemy_road[1];
					if (m_enemy->cord[1] == game->pl_pos[1] && m_enemy->cord[0] == game->pl_pos[0])
						mlx_close_window(game->mlx);
				}
			}
			m_enemy = m_enemy->next;
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
	map.collect = NULL;
	map.enemys = NULL;
	if (argc == 2)
	{
		fd = open_file(argv[1]);
		measure_map(&map, fd);
		fd = open_file(argv[1]);
		create_map(&map, fd);
		is_valid_chars(&map);
		bfs(&map, map.ex_pos);
		init_images(&map);
		put_images(&map);
		mlx_key_hook(map.mlx, &moves, &map);
		mlx_loop_hook(map.mlx, &generic_loop, &map);
		mlx_loop(map.mlx);
		mlx_terminate(map.mlx);
	}
	return (0);
}
