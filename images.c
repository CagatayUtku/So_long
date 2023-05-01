/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 10:27:11 by Cutku             #+#    #+#             */
/*   Updated: 2023/05/01 22:55:33 by Cutku            ###   ########.fr       */
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

	map->mlx = mlx_init(map->width * 80, map->height * 80, "so_long", 1);
	if (!map->mlx)
		return ;
	map->bg = xpm_to_image(map, "./images/bcg.xpm42");
	map->pl = xpm_to_image(map, "./images/pl1.xpm42");
	map->wall = xpm_to_image(map, "./images/box.xpm42");
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
	int	i;
	int	j;

	i = -1;
	while (++i < game->height)
	{
		j = -1;
		while (++j < game->width)
		{
			mlx_image_to_window(game->mlx, game->bg, j * 80, i * 80);
			if (game->map[i][j] == '1')
				mlx_image_to_window(game->mlx, game->wall, j * 80, i * 80);
			if (game->map[i][j] == 'C')
				mlx_image_to_window(game->mlx, which_object(&game->collect, i, j), j * 80, i * 80);
		}
	}
	i = -1;
	while (++i < game->height)
	{
		j = -1;
		while (++j < game->width)
		{
		if (game->map[i][j] == 'X')
			mlx_image_to_window(game->mlx, which_object(&game->enemys, i, j), j * 80, i * 80);
		}
	}
	mlx_image_to_window(game->mlx, game->pl, game->pl_pos[1] * 80, game->pl_pos[0] * 80);
}
