/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukibrok <mukibrok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 00:32:21 by mukibrok          #+#    #+#             */
/*   Updated: 2025/08/12 17:54:02 by mukibrok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

int split_len(char **split)
{
	int count = 0;
	while (split[count])
		count++;
	return (count);
}

void	print_map(t_game *map)
{
	if (!map || !map->map)
	{
		printf("Map is not initialized.\n");
		return;
	}
	printf("NO :%s\n", map->textures[NORTH_TEX] ? map->textures[NORTH_TEX] : "None");
	printf("SO Texture: %s\n", map->textures[SOUTH_TEX] ? map->textures[SOUTH_TEX] : "None");
	printf("WE Texture: %s\n", map->textures[WEST_TEX] ? map->textures[WEST_TEX] : "None");
	printf("EA Texture: %s\n", map->textures[EAST_TEX] ? map->textures[EAST_TEX] : "None");
	printf("Floor Color: R=%d, G=%d, B=%d\n",
		map->floor_color.red, map->floor_color.green, map->floor_color.blue);
	printf("Ceiling Color: R=%d, G=%d, B=%d\n",
		map->ceiling_color.red, map->ceiling_color.green, map->ceiling_color.blue);
	printf("Map dimensions: %d x %d\n", map->map_width, map->map_height);
	printf("Map contents:\n");
	for (int i = 0; i < map->map_height; i++)
	{
		if (map->map[i])
			printf("%s\n", map->map[i]);
		else
			printf("\n");
	}
}