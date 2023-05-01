/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 05:11:09 by Cutku             #+#    #+#             */
/*   Updated: 2023/05/01 23:00:07 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_valid_chars(t_game *map)
{
	int	i;
	int	j;

	map->num_collect = 0;
	map->num_enemy = 0;
	map->exit = 0;
	map->player = 0;
	i = -1;
	while (map->map[++i] != NULL)
	{
		j = -1;
		while (map->map[i][++j] != '\0')
			is_valid_map(map, i, j);
	}
	if (map->player != 1)
		error_message(PLAYER_ERR, map);
	if (map->exit != 1)
		error_message(EXIT_ERR, map);
	if (map->num_collect < 1)
		error_message(COLLECT_ERR, map);
	if (map->num_enemy < 1)
		error_message(ENEMY_ERR, map);
	return (1);
}

void	is_valid_map(t_game *map, int i, int j)
{
	if (ft_strchr(CHAR_SET, map->map[i][j]) != 0)
	{
		if ((i == 0 || i == map->height - 1) && map->map[i][j] != '1')
			error_message(WALL_ERR, map);
		else if ((j == 0 || j == map->width - 1) && map->map[i][j] != '1')
			error_message(WALL_ERR, map);
		else if (map->map[i][j] == 'C')
		{
			map->num_collect++;
			add_object(&map->collect, i, j);
		}
		else if (map->map[i][j] == 'X')
		{
			map->num_enemy++;
			add_object(&map->enemys, i, j);
		}
		else if (map->map[i][j] == 'E')
		{
			map->exit++;
			map->ex_pos[0] = i;
			map->ex_pos[1] = j;
		}
		else if (map->map[i][j] == 'P')
		{
			map->player++;
			map->pl_pos[0] = i;
			map->pl_pos[1] = j;
		}
	}
	else
		error_message(W_INPUT, map);
}

void	error_message(char *str, t_game *map)
{
	ft_putstr_fd(str, 2);
	free_char_dubleptr(map->map, map->height);
	exit(EXIT_FAILURE);
}
