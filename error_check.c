/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 05:11:09 by Cutku             #+#    #+#             */
/*   Updated: 2023/05/11 23:20:04 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_valid_chars(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->map[++i] != NULL)
	{
		j = -1;
		while (game->map[i][++j] != '\0')
			is_valid_map(game, i, j);
	}
	if (num_object(game->player) != 1)
		error_message(PLAYER_ERR, game);
	if (num_object(game->exit) != 1)
		error_message(EXIT_NO, game);
	if (num_object(game->collect) < 1)
		error_message(COLLECT_ERR, game);
	if (num_object(game->enemys) < 1)
		error_message(ENEMY_ERR, game);
	if (bfs(game, game->exit->cord) == 0)
		error_message(EXIT_PATH, game);
	return (1);
}

void	is_valid_map(t_game *game, int i, int j)
{
	if (ft_strchr(CHAR_SET, game->map[i][j]) != 0)
	{
		if ((i == 0 || i == game->height - 1) && game->map[i][j] != '1')
			error_message(WALL_ERR, game);
		else if ((j == 0 || j == game->width - 1) && game->map[i][j] != '1')
			error_message(WALL_ERR, game);
		else if (game->map[i][j] == 'C')
			add_object(&game->collect, i, j);
		else if (game->map[i][j] == 'X')
			add_object(&game->enemys, i, j);
		else if (game->map[i][j] == 'E')
			add_object(&game->exit, i, j);
		else if (game->map[i][j] == 'P')
			add_object(&game->player, i, j);
	}
	else
		error_message(W_INPUT, game);
}

void	error_message(char *str, t_game *game)
{
	ft_putstr_fd(str, 2);
	free_char_dubleptr(game->map, game->height);
	exit(EXIT_FAILURE);
}
