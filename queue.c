/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 03:35:26 by Cutku             #+#    #+#             */
/*   Updated: 2023/05/12 18:43:44 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	enqueue(t_queue **front, t_queue **rear, int *data)
{
	t_queue	*new;

	new = NULL;
	new = (t_queue *)malloc(sizeof(t_queue));
	if (!new)
	{
		perror ("malloc");
		exit (EXIT_FAILURE);
	}
	new->data[0] = data[0];
	new->data[1] = data[1];
	new->next = NULL;
	if (*front == NULL)
	{
		*front = new;
		*rear = new;
	}
	else
	{
		(*rear)->next = new;
		*rear = new;
	}
}

void	dequeue(t_queue **front)
{
	t_queue	*temp;

	if (*front != NULL)
	{
		temp = *front;
		*front = (*front)->next;
		free(temp);
	}
	else
		ft_putstr_fd("Queue is empty.\n", 2);
}
