/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 10:27:11 by Cutku             #+#    #+#             */
/*   Updated: 2023/05/12 06:02:02 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

mlx_image_t	*xpm_to_image(t_game *game, char *path)
{
	xpm_t			*xpm;
	mlx_image_t		*img;
	int				fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("File couldn't open ! ");
		exit (EXIT_FAILURE);
	}
	xpm = mlx_load_xpm42(path);
	if (!xpm)
	{
		perror("Xpm Error");
		exit(EXIT_FAILURE);
	}
	img = mlx_texture_to_image(game->mlx, &xpm->texture);
	if (!img)
	{	
		perror("Image Error");
		exit(EXIT_FAILURE);
	}
	mlx_delete_xpm42(xpm);
	close(fd);
	return (img);
}

void	init_images(t_game *map)
{
	t_object	*temp;

	map->mlx = mlx_init(map->width * 80, (map->height * 80) + 50, "so_long", 1);
	if (!map->mlx)
		return ;
	map->bg = xpm_to_image(map, "./images/bcg.xpm42");
	map->wall = xpm_to_image(map, "./images/box.xpm42");
	map->exit->image = xpm_to_image(map, "./images/exit1.xpm42");
	map->player->image = xpm_to_image(map, "./images/pl1.xpm42");
	map->success = xpm_to_image(map, "./images/success.xpm42");
	map->fail = xpm_to_image(map, "./images/fail.xpm42");
	temp = map->collect;
	while (temp)
	{
		temp->image = xpm_to_image(map, "./images/collect.xpm42");
		temp = temp->next;
	}
	temp = map->enemys;
	while (temp)
	{
		temp->image = xpm_to_image(map, "./images/enemy_left.xpm42");
		temp = temp->next;
	}
}

void	put_images(t_game *game)
{
	int			i;
	int			j;
	t_object	*temp;

	i = -1;
	while (++i < game->height)
	{
		j = -1;
		while (++j < game->width)
		{
			img_window(game->mlx, game->bg, j, i);
			if (game->map[i][j] == '1')
				img_window(game->mlx, game->wall, j, i);
			if (game->map[i][j] == 'C')
				img_window(game->mlx, which_object(&game->collect, i, j), j, i);
		}
	}
	temp = game->enemys;
	while (temp)
	{
		img_window(game->mlx, temp->image, temp->cord[1], temp->cord[0]);
		temp = temp->next;
	}
	temp = game->player;
	img_window(game->mlx, temp->image, temp->cord[1], temp->cord[0]);
}

void	scoreboard(t_game *game)
{
	char	*score;

	mlx_delete_image(game->mlx, game->score);
	mlx_delete_image(game->mlx, game->move);
	game->move = mlx_put_string(game->mlx, "Move :", 20, \
		game->height * 80 + 10);
	score = ft_itoa(game->num_move);
	if (!score)
		return ;
	game->score = mlx_put_string(game->mlx, score, 100, game->height * 80 + 10);
	free(score);
}

void	img_window(mlx_t *mlx, mlx_image_t	*img, int j, int i)
{
	mlx_image_to_window(mlx, img, j * 80, i * 80);
}
