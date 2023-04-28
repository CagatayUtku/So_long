/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 04:32:16 by Cutku             #+#    #+#             */
/*   Updated: 2023/04/28 17:06:28 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	add_collectible(t_collect **first, int i, int j)
{
	t_collect	*new;
	t_collect	*last;

	new = (t_collect *)malloc(sizeof(t_collect));
	new->cord[0] = i;
	new->cord[1] = j;
	new->collectible = NULL;
	new->next = NULL;
	if (*first == NULL)
		*first = new;
	else
	{
		last = *first;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}

void	remove_collectible(t_game *game, t_collect **first, int i, int j)
{
	t_collect	*del;

	del = *first;
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

mlx_image_t	*which_collectible(t_collect **first, int i, int j)
{
	t_collect	*temp;

	temp = *first;
	while (temp)
	{
		if (temp->cord[0] == i && temp->cord[1] == j)
			return (temp->collectible);
		temp = temp->next;
	}
	return (NULL);
}
