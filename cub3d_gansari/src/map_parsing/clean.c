/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukibrok <mukibrok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 22:46:12 by mukibrok          #+#    #+#             */
/*   Updated: 2025/08/14 17:15:32 by mukibrok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
}
