/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 04:32:16 by Cutku             #+#    #+#             */
/*   Updated: 2023/04/27 08:20:47 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	add_collectible(t_game *game, int i, int j)
{
	t_collect *new;
	t_collect *last;

	new = (t_collect *)malloc(sizeof(t_collect));
	new->cord[0] = i;
	new->cord[1] = j;
	new->collectible = NULL;
	new->next = NULL;
	if (game->keys == NULL)
		game->keys = new;
	else
	{
		last = game->keys;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}

void	remove_collectible(t_game *game, int i, int j)
{
	t_collect	*del;

	del = game->keys;
	while (del)
	{
		if (del->cord[0] == i && del->cord[1] == j)
		{
			mlx_delete_image(game->mlx, del->collectible);
			break ;
		}
		del = del->next;
	}
}

mlx_image_t	*which_collectible(t_game *game, int i, int j)
{
	t_collect	*temp;

	temp = game->keys;
	while (temp)
	{
		if (temp->cord[0] == i && temp->cord[1] == j)
			return (temp->collectible);
		temp = temp->next;
	}
	return (NULL);
}