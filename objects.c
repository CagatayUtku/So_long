/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 04:32:16 by Cutku             #+#    #+#             */
/*   Updated: 2023/05/05 22:27:57 by Cutku            ###   ########.fr       */
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
	t_object	*tail;
	int			k;

	del = *first;
	tail = del;
	k = 0;
	while (del)
	{
		if (del->cord[0] == i && del->cord[1] == j)
		{
			if (k == 0)
			{
				*first = (*first)->next;
				mlx_delete_image(game->mlx, del->image);
				free (del);
				return ;
			}
			tail->next = del->next;
			mlx_delete_image(game->mlx, del->image);
			free(del);
			return ;
		}
		tail = del;
		del = del->next;
		++k;
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

int	num_object(t_object *first)
{
	t_object	*temp;
	int			i;

	temp = first;
	i = 0;
	while (temp)
	{
		++i;
		temp = temp->next;
	}
	return (i);
}
