/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 04:32:16 by Cutku             #+#    #+#             */
/*   Updated: 2023/05/01 23:00:50 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	add_object(t_object **first, int i, int j)
{
	t_object	*new;
	t_object	*last;

	new = (t_object *)malloc(sizeof(t_object));
	new->cord[0] = i;
	new->cord[1] = j;
	new->image = NULL;
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

void	remove_object(t_game *game, t_object **first, int i, int j)
{
	t_object	*del;

	del = *first;
	while (del)
	{
		if (del->cord[0] == i && del->cord[1] == j)
		{
			mlx_delete_image(game->mlx, del->image);
			return ;
		}
		del = del->next;
	}
}

mlx_image_t	*which_object(t_object **first, int i, int j)
{
	t_object	*temp;

	temp = *first;
	while (temp)
	{
		if (temp->cord[0] == i && temp->cord[1] == j)
			return (temp->image);
		temp = temp->next;
	}
	return (NULL);
}
