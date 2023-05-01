/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 05:09:20 by Cutku             #+#    #+#             */
/*   Updated: 2023/05/01 23:14:13 by Cutku            ###   ########.fr       */
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
