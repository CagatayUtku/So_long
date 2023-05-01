/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 04:03:46 by Cutku             #+#    #+#             */
/*   Updated: 2023/05/01 23:14:04 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	**create_visited(t_game *map)
{
	int	**visited;
	int	i;
	int	j;

	visited = (int **)malloc((map->height) * sizeof(int *));
	if (!visited)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < map->height)
	{
		visited[i] = ft_calloc(map->width, sizeof(int));
		if (!visited[i])
		{
			perror("malloc");
			free_int_dubleptr(visited, i);
			exit(EXIT_FAILURE);
		}
	}
	return (visited);
}

int	bfs(t_game *map, int target[2])
{
	map->visited = create_visited(map);
	map->visited[map->pl_pos[0]][map->pl_pos[1]] = 1;
	enqueue(&map->front, &map->rear, map->pl_pos);
	while (map->front != NULL)
	{
		if (check_neighbors(map, -1, 0, target))
			return (clean_bfs(map), 1);
		if (check_neighbors(map, 1, 0, target))
			return (clean_bfs(map), 1);
		if (check_neighbors(map, 0, -1, target))
			return (clean_bfs(map), 1);
		if (check_neighbors(map, 0, 1, target))
			return (clean_bfs(map), 1);
		dequeue(&map->front);
	}
	return (clean_bfs(map), 0);
}

int	check_neighbors(t_game *game, int i, int j, int target[2])
{
	int	temp[2];

	temp[0] = game->front->data[0] + i;
	temp[1] = game->front->data[1] + j;
	if (game->map[temp[0]][temp[1]] != '1' && \
		game->visited[temp[0]][temp[1]] != 1)
	{
		game->visited[temp[0]][temp[1]] = 1;
		enqueue(&game->front, &game->rear, temp);
		if (temp[0] == target[0] && temp[1] == target[1])
		{
			game->enemy_road[0] = game->front->data[0];
			game->enemy_road[1] = game->front->data[1];
			return (1);
		}
	}
	return (0);
}
