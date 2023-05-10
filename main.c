/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 06:43:56 by Cutku             #+#    #+#             */
/*   Updated: 2023/05/09 18:58:18 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	moves(mlx_key_data_t k_data, void *param)
{
	t_game	*game;

	game = param;
	if ((k_data.action == MLX_PRESS || k_data.action == MLX_REPEAT))
	{
		if (k_data.key == MLX_KEY_ESCAPE)
		{
			free_all(game);
			mlx_close_window(game->mlx);
			exit(0);
		}
		if (game->state == 1)
		{
			if (k_data.key == MLX_KEY_UP || k_data.key == MLX_KEY_W)
				if (player_movement(game, game->player->cord[0] - 1, game->player->cord[1]))
					game->player->image->instances->y -= 80;
			if (k_data.key == MLX_KEY_DOWN || k_data.key == MLX_KEY_S)
				if (player_movement(game, game->player->cord[0] + 1, game->player->cord[1]))
					game->player->image->instances->y += 80;
			if (k_data.key == MLX_KEY_LEFT || k_data.key == MLX_KEY_A)
				if (player_movement(game, game->player->cord[0], game->player->cord[1] - 1))
					game->player->image->instances->x -= 80;
			if (k_data.key == MLX_KEY_RIGHT || k_data.key == MLX_KEY_D)
				if (player_movement(game, game->player->cord[0], game->player->cord[1] + 1))
					game->player->image->instances->x += 80;
		}
	}
}

int	player_movement(t_game *game, int i, int j)
{
	if (game->state == 1 && game->map[i][j] != '1')
	{
		if (!is_enemy(game->enemys, i, j))
		{
			if (game->map[i][j] == 'C')
			{
				remove_object(game, &game->collect, i, j);
				if (game->collect == NULL)
					img_window(game->mlx, game->exit->image, game->exit->cord[1], game->exit->cord[0]);
			}
			if (game->collect == NULL && (i == game->exit->cord[0] && j == game->exit->cord[1]))
			{
				game->state = 0;
				mlx_delete_image(game->mlx, game->exit->image);
				game->exit->image = xpm_to_image(game, "./images/exit2.xpm42");
				img_window(game->mlx, game->exit->image, game->exit->cord[1], game->exit->cord[0]);
			}
			game->player->cord[0] = i;
			game->player->cord[1] = j;
			return (1);
		}
		game->state = -1;
		free_all(game);
		img_window(game->mlx, game->fail, 1, 1);
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
	t_game		*game;
	t_object	*m_enemy;
	static int	time = 0;
	static int	photo = 0;

	game = param;
	time++;
	m_enemy = game->enemys;
	if (time % 15 == 0 && game->state == 1)
	{
		photo++;
		while (m_enemy && photo % 2 != 0)
		{
			mlx_delete_image(game->mlx, m_enemy->image);
			m_enemy->image = xpm_to_image(game, "./images/enemy_right.xpm42");
			img_window(game->mlx, m_enemy->image, m_enemy->cord[1], m_enemy->cord[0]);
			m_enemy = m_enemy->next;
		}
		if (time % 30 == 0)
		{
			m_enemy = game->enemys;
			while (m_enemy)
			{
				bfs(game, m_enemy->cord);
				mlx_delete_image(game->mlx, m_enemy->image);
				m_enemy->image = xpm_to_image(game, "./images/enemy_left.xpm42");
				img_window(game->mlx, m_enemy->image, m_enemy->cord[1], m_enemy->cord[0]);
				enemy_move(game, m_enemy, m_enemy->cord);
				if (game->state == -1)
				{
					m_enemy = NULL;
				}
				else
					m_enemy = m_enemy->next;
			}
		}
	}
	else if (time % 20 == 0 && game->state == 0)
	{
		if (game->exit->cord[0] > 1)
		{
			if (game->player)
				remove_object(game, &game->player, game->player->cord[0], game->player->cord[1]);
			game->exit->image->instances->y -= 80;
			game->exit->cord[0] -= 1;
		}
		else
		{
			free_all(game);
			img_window(game->mlx, game->success, 3, 3);
			game->state = -1;
		}
	}
}

void	enemy_move(t_game *game, t_object *m_enemy, int cord[2])
{
	int	num;
	int	pl_cord[2];

	pl_cord[0] = game->player->cord[0];
	pl_cord[1] = game->player->cord[1];
	if (cord[0] != game->enemy_road[0])
	{
		if (!is_enemy(game->enemys, game->enemy_road[0], game->enemy_road[1]))
		{
			num = game->enemy_road[0] - cord[0];
			m_enemy->image->instances->y += (80 * num);
			cord[0] = game->enemy_road[0];
			if (cord[1] == game->player->cord[1] && cord[0] == pl_cord[0])
			{
				game->state = -1;
				free_all(game);
				img_window(game->mlx, game->fail, 1, 1);
			}
		}
	}
	else if (cord[1] != game->enemy_road[1])
	{
		if (!is_enemy(game->enemys, game->enemy_road[0], game->enemy_road[1]))
		{
			num = game->enemy_road[1] - cord[1];
			m_enemy->image->instances->x += (80 * num);
			cord[1] = game->enemy_road[1];
			if (cord[1] == pl_cord[1] && cord[0] == pl_cord[0])
			{
				game->state = -1;
				free_all(game);
				img_window(game->mlx, game->fail, 1, 1);
			}
		}
	}
}

void	leaks(void)
{
	system("leaks so_long");
}

int	main(int argc, char **argv)
{
	t_game	map;
	t_queue	*front;
	t_queue	*rear;
	int		fd;

	atexit(&leaks);
	map.front = NULL;
	map.rear = NULL;
	map.collect = NULL;
	map.enemys = NULL;
	map.player = NULL;
	map.state = 1;
	if (argc == 2)
	{
		fd = open_file(argv[1]);
		measure_map(&map, fd);
		fd = open_file(argv[1]);
		create_map(&map, fd);
		is_valid_chars(&map);
		bfs(&map, map.exit->cord);
		init_images(&map);
		put_images(&map);
		mlx_key_hook(map.mlx, &moves, &map);
		mlx_loop_hook(map.mlx, &generic_loop, &map);
		mlx_loop(map.mlx);
		mlx_terminate(map.mlx);
		free_all(&map);
	}
	return (0);
}
