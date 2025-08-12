/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukibrok <mukibrok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 00:32:21 by mukibrok          #+#    #+#             */
/*   Updated: 2025/08/12 23:45:39 by mukibrok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

void	init_map(t_game *map)
{
	int	i;

	i = -1;
	map->map = NULL;
	map->map_width = 0;
	map->map_height = 0;
	while (++i < TEX_COUNT)
		map->textures[i] = NULL;
	map->floor_color = (t_color){-1, -1, -1};
	map->ceiling_color = (t_color){-1, -1, -1};
	map->player.x = 0.0;
	map->player.y = 0.0;
	map->player.direction = 0.0; // Assuming player direction is a double
}

int	split_len(char **split)
{
	int	count;

	count = 0;
	while (split[count])
		count++;
	return (count);
}

int	space_count(char *line)
{
	int	count;

	count = 1;
	while (*line)
	{
		if (ft_isspace(*line))
			count++;
		line++;
	}
	return (count);
}

int	free_double_ptr(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return (EXIT_FAILURE);
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (EXIT_SUCCESS);
}

void	print_map(t_game *map)
{
	if (!map || !map->map)
	{
		printf("Map is not initialized.\n");
		return;
	}
	printf("NO :%s", map->textures[NORTH_TEX] ? map->textures[NORTH_TEX] : "None");
	printf("SO :%s", map->textures[SOUTH_TEX] ? map->textures[SOUTH_TEX] : "None");
	printf("WE :%s", map->textures[WEST_TEX] ? map->textures[WEST_TEX] : "None");
	printf("EA :%s", map->textures[EAST_TEX] ? map->textures[EAST_TEX] : "None");
	printf("Floor Color: R=%d, G=%d, B=%d\n",
		map->floor_color.red, map->floor_color.green, map->floor_color.blue);
	printf("Ceiling Color: R=%d, G=%d, B=%d\n",
		map->ceiling_color.red, map->ceiling_color.green, map->ceiling_color.blue);
	printf("Map dimensions: %d x %d\n", map->map_width, map->map_height);
	printf("Map contents:\n");
	for (int i = 0; i < map->map_height; i++)
	{
		if (map->map[i])
			printf("%s", map->map[i]);
	}
	printf("\n");
}