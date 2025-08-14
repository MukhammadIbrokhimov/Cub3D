/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukibrok <mukibrok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 22:46:12 by mukibrok          #+#    #+#             */
/*   Updated: 2025/08/14 13:04:59 by mukibrok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

/**
 * Free the allocated memory for the map and textures
 * @param map Pointer to the game structure containing the map and textures
 */

void	cleanup_map(t_map *map)
{
	if (!map)
		return ;
	if (map->grid)
		free_double_ptr(map->grid);
	int i = -1;
	while (++i < TEX_COUNT)
	{
		if (map->textures[i])
			free(map->textures[i]);
	}
}
