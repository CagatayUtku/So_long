/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 05:09:20 by Cutku             #+#    #+#             */
/*   Updated: 2023/05/08 17:39:07 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	clean_bfs(t_game *game)
{
	t_queue	*del;

	while (game->front != NULL)
		dequeue(&game->front);
	game->rear = NULL;
	free_int_dubleptr(game->visited, game->height);
}

void	free_char_dubleptr(char **ptr, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		free(ptr[i]);
	free(ptr);
}

void	free_int_dubleptr(int **ptr, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		free(ptr[i]);
	free(ptr);
}

void	free_all(t_game *game)
{
	t_object *del;

	while (game->enemys)
	{
		del = game->enemys;
		game->enemys = game->enemys->next;
		mlx_delete_image(game->mlx, del->image);
		free(del);
	}
	while (game->collect)
	{
		del = game->collect;
		game->collect = game->collect->next;
		mlx_delete_image(game->mlx, del->image);
		free(del);
	}
	if (game->player)
	{
		del = game->player;
		game->player = game->player->next;
		mlx_delete_image(game->mlx, del->image);
		free(del);
	}
	if (game->exit)
	{
		del = game->exit;
		game->exit = game->exit->next;
		mlx_delete_image(game->mlx, del->image);
		free(del);
	}
	mlx_delete_image(game->mlx, game->bg);
	mlx_delete_image(game->mlx, game->wall);
	free_char_dubleptr(game->map, game->height);
}
