/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 03:58:37 by Cutku             #+#    #+#             */
/*   Updated: 2023/05/12 04:56:40 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	enemy_loop(void *param)
{
	t_game		*game;
	t_object	*m_enemy;
	static int	time = 0;

	game = param;
	time++;
	m_enemy = game->enemys;
	if (time % 15 == 0 && game->state == 1)
	{
		enemy_image_change(game);
		if (time % 30 == 0)
		{
			while (game->state == 1 && m_enemy)
			{
				bfs(game, m_enemy->cord);
				enemy_move(game, m_enemy, m_enemy->cord);
				if (game->state != -1)
					m_enemy = m_enemy->next;
			}
		}
	}
	else if (time % 20 == 0 && game->state == 0)
		final_animation(game);
	time = time % 100;
}

void	enemy_move(t_game *game, t_object *m_enemy, int cord[2])
{
	if (!is_enemy(game->enemys, game->enemy_road[0], game->enemy_road[1]))
	{
		m_enemy->image->instances->y += (80 * (game->enemy_road[0] - cord[0]));
		m_enemy->image->instances->x += (80 * (game->enemy_road[1] - cord[1]));
		cord[0] = game->enemy_road[0];
		cord[1] = game->enemy_road[1];
		if (cord[1] == game->player->cord[1] \
		&& cord[0] == game->player->cord[0])
		{
			game->state = -1;
			free_all(game);
			img_window(game->mlx, game->fail, 1, 1);
		}
	}
}

void	enemy_image_change(t_game *game)
{
	static int	photo = 0;
	t_object	*enemy;

	++photo;
	enemy = game->enemys;
	while (enemy)
	{
		mlx_delete_image(game->mlx, enemy->image);
		if (photo % 2 != 0)
			enemy->image = xpm_to_image(game, "./images/enemy_right.xpm42");
		else
			enemy->image = xpm_to_image(game, "./images/enemy_left.xpm42");
		img_window(game->mlx, enemy->image, enemy->cord[1], enemy->cord[0]);
		enemy = enemy->next;
	}
	photo = photo % 100;
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

void	final_animation(t_game *game)
{
	if (game->exit->cord[0] > 1)
	{
		if (game->player)
			remove_object(game, &game->player, \
			game->player->cord[0], game->player->cord[1]);
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
