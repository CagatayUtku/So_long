/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 04:03:46 by Cutku             #+#    #+#             */
/*   Updated: 2023/04/29 06:16:38 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	**create_visited(t_game *map)
{
	int	**visited;
	int	i;
	int	j;

	visited = (int **)malloc((map->height + 1) * sizeof(int *));
	if (!visited)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < map->height)
	{
		visited[i] = malloc(map->width * sizeof(int));
		if (!visited[i])
		{
			perror("malloc");
			// free_char_dubleptr(visited, i);
			exit(EXIT_FAILURE);
		}
		j = -1;
		while (++j < map->width)
			visited[i][j] = 0;
	}
	visited[i] = NULL;
	return (visited);
}

t_parent	**create_parent(t_game *map)
{
	t_parent	**visited;
	int			x;
	int			y;

	visited = (t_parent **)malloc((map->height + 1) * sizeof(t_parent *));
	if (!visited)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	x = -1;
	while (++x < map->height)
	{
		visited[x] = malloc(map->width * sizeof(t_parent));
		if (!visited[x])
		{
			perror("malloc");
			// free_char_dubleptr(visited, i);
			exit(EXIT_FAILURE);
		}
	}
	visited[x] = NULL;
	return (visited);
}

int	bfs(t_game *map, t_queue **front, t_queue **rear, char last)
{
	int			**visited;
	t_parent	**parent;

	visited = create_visited(map);
	parent = create_parent(map);
	visited[map->pl_pos[0]][map->pl_pos[1]] = 1;
	parent[map->pl_pos[0]][map->pl_pos[1]].i = -1;
	parent[map->pl_pos[0]][map->pl_pos[1]].j = -1;
	enqueue(front, rear, map->pl_pos);
	while (*front != NULL)
	{
		if (check_up(front, rear, parent, visited, map, last))
			return (printf("Success\n"), 1);
		if (check_down(front, rear, parent, visited, map, last))
			return (printf("Success\n"), 1);
		if (check_left(front, rear, parent, visited, map, last))
			return (printf("Success\n"), 1);
		if (check_right(front, rear, parent, visited, map, last))
			return (printf("Success\n"), 1);
		dequeue(front);
	}
	return (printf("Fail\n"), 0);
}

int	check_left(t_queue **front, t_queue **rear, t_parent **parent, int **visited, t_game *map, char last)
{
	int	temp[2];

	temp[0] = (*front)->data[0];
	temp[1] = (*front)->data[1] - 1;
	if (map->map[temp[0]][temp[1]] != '1' && visited[temp[0]][temp[1]] != 1)
	{
		visited[temp[0]][temp[1]] = 1;
		parent[temp[0]][temp[1]].i = (*front)->data[0];
		parent[temp[0]][temp[1]].j = (*front)->data[1];
		enqueue(front, rear, temp);
		if (map->map[temp[0]][temp[1]] == last)
			return (printf_shortest(map, parent, (*front)->data[0], temp[1], last),1);
	}
	return (0);
}

int	check_right(t_queue **front, t_queue **rear, t_parent **parent, int **visited, t_game *map, char last)
{
	int	temp[2];

	temp[0] = (*front)->data[0];
	temp[1] = (*front)->data[1] + 1;
	if (map->map[temp[0]][temp[1]] != '1' && visited[temp[0]][temp[1]] != 1)
	{
		visited[temp[0]][temp[1]] = 1;
		parent[temp[0]][temp[1]].i = (*front)->data[0];
		parent[temp[0]][temp[1]].j = (*front)->data[1];
		enqueue(front, rear, temp);
		if (map->map[temp[0]][temp[1]] == last)
			return (printf_shortest(map, parent, (*front)->data[0], temp[1], last),1);
	}
	return (0);
}
int	check_up(t_queue **front, t_queue **rear, t_parent **parent, int **visited, t_game *map, char last)
{
	int	temp[2];

	temp[0] = (*front)->data[0] + 1;
	temp[1] = (*front)->data[1];
	if (map->map[temp[0]][temp[1]] != '1' && visited[temp[0]][temp[1]] != 1)
	{
		visited[temp[0]][temp[1]] = 1;
		parent[temp[0]][temp[1]].i = (*front)->data[0];
		parent[temp[0]][temp[1]].j = (*front)->data[1];
		enqueue(front, rear, temp);
		if (map->map[temp[0]][temp[1]] == last)
			return (printf_shortest(map, parent, (*front)->data[0], temp[1], last),1);
	}
	return (0);
}

int	check_down(t_queue **front, t_queue **rear, t_parent **parent, int **visited, t_game *map, char last)
{
	int	temp[2];

	temp[0] = (*front)->data[0] - 1;
	temp[1] = (*front)->data[1];
	if (map->map[temp[0]][temp[1]] != '1' && visited[temp[0]][temp[1]] != 1)
	{
		visited[temp[0]][temp[1]] = 1;
		parent[temp[0]][temp[1]].i = (*front)->data[0];
		parent[temp[0]][temp[1]].j = (*front)->data[1];
		enqueue(front, rear, temp);
		if (map->map[temp[0]][temp[1]] == last)
			return (printf_shortest(map, parent, (*front)->data[0], temp[1], last),1);
	}
	return (0);
}

void	printf_shortest(t_game *map, t_parent **parent, int row, int col, char last)
{
	int	temp;
	int	data[2];
	int	i;
	t_queue *del;

	while (map->front != NULL)
	{
		del = map->front;
		map->front = (map->front)-> next;
		free(del);
	}
	if (last ==  'X' && parent[row][col].i != -1)
	{
		map->enemy_road[0] = parent[row][col].i;
		map->enemy_road[1] = parent[row][col].j;
		printf("(%d %d)\n",map->enemy_road[0], map->enemy_road[1]);
		// while (parent[row][col].i != -1)
		// {
		// 	temp = row;
		// 	printf("[%d - %d]", parent[row][col].i, parent[row][col].j);
		// 	row = parent[row][col].i;
		// 	col = parent[temp][col].j;
		// }
	}
}
