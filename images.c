/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 10:27:11 by Cutku             #+#    #+#             */
/*   Updated: 2023/04/25 10:52:49 by Cutku            ###   ########.fr       */
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
