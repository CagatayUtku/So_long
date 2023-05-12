/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 05:09:20 by Cutku             #+#    #+#             */
/*   Updated: 2023/05/13 01:49:53 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	clean_bfs(t_game *game)
{
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
	if (game->exit)
	{
		mlx_delete_image(game->mlx, game->bg);
		mlx_delete_image(game->mlx, game->wall);
		free_char_dubleptr(game->map, game->height);
	}
	free_objects(game, &game->enemys);
	free_objects(game, &game->collect);
	free_objects(game, &game->player);
	free_objects(game, &game->exit);
}

void	free_objects(t_game *game, t_object **obj)
{
	t_object	*del;

	while (*obj != NULL)
	{
		del = *obj;
		*obj = (*obj)->next;
		mlx_delete_image(game->mlx, del->image);
		free(del);
	}
}
