/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 06:43:56 by Cutku             #+#    #+#             */
/*   Updated: 2023/05/12 04:59:17 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	leaks(void)
{
	system("leaks so_long");
}

void	init_struct(t_game *game)
{
	game->front = NULL;
	game->rear = NULL;
	game->collect = NULL;
	game->enemys = NULL;
	game->player = NULL;
	game->state = 1;
	game->num_move = 0;
}

int	main(int argc, char **argv)
{
	t_game	game;
	int		fd;

	atexit(&leaks);
	if (argc == 2)
	{
		init_struct(&game);
		fd = open_file(argv[1]);
		measure_map(&game, fd);
		fd = open_file(argv[1]);
		create_map(&game, fd);
		is_valid_chars(&game);
		init_images(&game);
		put_images(&game);
		mlx_key_hook(game.mlx, &key_loop, &game);
		mlx_loop_hook(game.mlx, &enemy_loop, &game);
		mlx_loop(game.mlx);
		mlx_terminate(game.mlx);
		free_all(&game);
	}
	return (0);
}
