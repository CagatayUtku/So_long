/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 23:30:23 by Cutku             #+#    #+#             */
/*   Updated: 2023/05/13 01:45:46 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	key_loop(mlx_key_data_t k_data, void *param)
{
	t_game	*game;

	game = param;
	if ((k_data.action == MLX_PRESS || k_data.action == MLX_REPEAT))
	{
		if (k_data.key == MLX_KEY_ESCAPE)
		{
			free_all(game);
			mlx_close_window(game->mlx);
			mlx_delete_image(game->mlx, game->success);
			mlx_delete_image(game->mlx, game->fail);
			exit(EXIT_SUCCESS);
		}
		if (game->state == 1)
			player_key_press(k_data, game);
	}
}

void	player_key_press(mlx_key_data_t k_data, t_game *game)
{
	t_object	*player;

	player = game->player;
	if (k_data.key == MLX_KEY_UP || k_data.key == MLX_KEY_W)
		if (player_movement(game, player->cord[0] - 1, player->cord[1]))
			player->image->instances->y -= 80;
	if (k_data.key == MLX_KEY_DOWN || k_data.key == MLX_KEY_S)
		if (player_movement(game, player->cord[0] + 1, player->cord[1]))
			player->image->instances->y += 80;
	if (k_data.key == MLX_KEY_LEFT || k_data.key == MLX_KEY_A)
		if (player_movement(game, player->cord[0], player->cord[1] - 1))
			player->image->instances->x -= 80;
	if (k_data.key == MLX_KEY_RIGHT || k_data.key == MLX_KEY_D)
		if (player_movement(game, player->cord[0], player->cord[1] + 1))
			player->image->instances->x += 80;
}

int	player_movement(t_game *game, int i, int j)
{
	if (game->state == 1 && game->map[i][j] != '1')
	{
		if (!is_enemy(game->enemys, i, j))
		{
			is_collectible(game, i, j);
			is_exit(game, i, j);
			game->player->cord[0] = i;
			game->player->cord[1] = j;
			++game->num_move;
			scoreboard(game);
			return (1);
		}
		game->state = -1;
		free_all(game);
		img_window(game->mlx, game->fail, 1, 1);
	}
	return (0);
}

void	is_collectible(t_game *game, int i, int j)
{
	t_object	*exit;

	exit = game->exit;
	if (game->map[i][j] == 'C')
	{
		remove_object(game, &game->collect, i, j);
		game->map[i][j] = '0';
		if (game->collect == NULL)
			img_window(game->mlx, exit->image, exit->cord[1], exit->cord[0]);
	}
}

void	is_exit(t_game *game, int i, int j)
{
	t_object	*exit;

	exit = game->exit;
	if (game->collect == NULL && (i == exit->cord[0] && j == exit->cord[1]))
	{
		game->state = 0;
		mlx_delete_image(game->mlx, exit->image);
		exit->image = xpm_to_image(game, "./images/exit2.xpm42");
		img_window(game->mlx, exit->image, exit->cord[1], exit->cord[0]);
	}
}
