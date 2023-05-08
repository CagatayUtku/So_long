/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 06:43:53 by Cutku             #+#    #+#             */
/*   Updated: 2023/05/06 19:05:48 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	open_file(char *map)
{
	int	len;
	int	fd;

	len = ft_strlen(map);
	if (len > 4 && (ft_strncmp(map + len - 4, ".ber", 4) == 0))
	{
		fd = open(map, O_RDONLY);
		if (fd < 0)
		{
			perror("Open");
			exit (EXIT_FAILURE);
		}
	}
	else
	{
		ft_putstr_fd("Not .ber file!\n", 2);
		exit (EXIT_FAILURE);
	}
	return (fd);
}

void	measure_map(t_game *map, int fd)
{
	char	*line;

	map->height = 0;
	line = get_next_line(fd);
	if (line != NULL)
		map->width = width_map(line);
	while (line != NULL)
	{
		free(line);
		map->height++;
		line = get_next_line(fd);
		if (line && map->width != width_map(line))
		{
			free(line);
			ft_putstr_fd("Map is not square, wrong width\n", 2);
			exit(EXIT_FAILURE);
		}
	}
	free (line);
	if (map->height == 0)
	{
		ft_putstr_fd("Empty File", 2);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

int	width_map(char *line)
{
	int	width;

	width = 0;
	if (line != NULL)
	{
		width = ft_strlen(line);
		if (line[width - 1] == '\n')
			width--;
	}
	return (width);
}

void	create_map(t_game *map, int fd)
{
	int		i;
	char	*temp;

	map->map = (char **)malloc((map->height + 1) * sizeof(char *));
	if (!map->map)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < map->height)
	{
		temp = get_next_line(fd);
		map->map[i] = ft_substr(temp, 0, map->width);
		free(temp);
		if (!map->map[i])
		{
			perror("malloc");
			free_char_dubleptr(map->map, i);
			exit(EXIT_FAILURE);
		}
	}
	map->map[i] = NULL;
	close(fd);
}
