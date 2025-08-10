/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukibrok <mukibrok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 23:59:49 by mukibrok          #+#    #+#             */
/*   Updated: 2025/08/11 00:31:48 by mukibrok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/Cub3D.h"

void	init_map(t_game *map)
{
	map->map = NULL;
	map->map_width = 0;
	map->map_height = 0;
	for (int i = 0; i < TEX_COUNT; i++)
		map->textures[i] = NULL;
	map->floor_color = (t_color){-1, -1, -1};
	map->ceiling_color = (t_color){-1, -1, -1};
	map->player.x = 0.0;
	map->player.y = 0.0;
	map->player.direction = 0.0; // Assuming player direction is a double
}

t_color parse_color(char *line)
{
	t_color	color;

	char **split = ft_split(line + 2, ',');
	if (split_len(split) != 3)
		return (t_color){-1, -1, -1};
	color.red = ft_atoi(split[0]);
	color.green = ft_atoi(split[1]);
	color.red = ft_atoi(split[2]);
	return (color);
}
