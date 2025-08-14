/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukibrok <mukibrok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 00:22:05 by mukibrok          #+#    #+#             */
/*   Updated: 2025/08/14 17:25:53 by mukibrok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


/**
 * Validate the file extension of the given filename
 * @param filename The name of the file to validate
 * @return true if the file has a valid .cub extension, false otherwise
 */

bool	validate_file_extension(char *filename)
{
	char	*ext;
	size_t		len;
	size_t		ext_len;

	ext = ".cub";
	len = ft_strlen(filename);
	ext_len = ft_strlen(ext);
	if (len < ext_len)
		return (false);
	return (ft_strcmp(filename + len - ext_len, ext) == 0);
}

/**
 * Validate the textures in the game map structure
 * @param map Pointer to the game structure containing the textures
 * @return true if all textures are valid, false otherwise
 */

bool	validate_texture(t_game *map)
{
	if (!map->textures.north.path || !map->textures.south.path ||
		!map->textures.west.path || !map->textures.east.path)
		return (print_error(ERR_MISSING_TEXTURE), false);
	return (true);
}

/**
 * Validate the color values in a t_color structure
 * @param color The t_color structure to validate
 * @return true if the color values are valid (0-255), false otherwise
 */

bool	validate_color(t_map *map)
{
	t_color	fcolor;
	t_color	ccolor;

	fcolor = map->floor_color;
	ccolor = map->ceiling_color;
	if (fcolor.red < 0 || fcolor.red > 255 ||
		fcolor.green < 0 || ccolor.green > 255 ||
		ccolor.blue < 0 || ccolor.blue > 255)
	{
		print_error(ERR_INVALID_COLOR);
		return (false);
	}
	return (true);
}

/**
 * Validate the characters in the map
 * Checks if the map contains only valid characters: WALL, EMPTY, SPACE, NORTH, SOUTH, EAST, WEST
 * @param map Pointer to the game structure containing the map
 * @return true if all characters are valid, false otherwise
 */

bool	validate_char(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	if (!map || !map->grid)
		return (print_error(ERR_INVALID), false);
	if (map->height <= 0 || map->width <= 0)
		return (print_error("Invalid map dimensions"), false);
	while (++i < map->height && map->grid[i])
	{
		j = -1;
		while (++j < (int)ft_strlen(map->grid[i]))
		{
			if (map->grid[i][j] != WALL && map->grid[i][j] != EMPTY &&
				map->grid[i][j] != SPACE && map->grid[i][j] != NORTH &&
				map->grid[i][j] != SOUTH && map->grid[i][j] != EAST &&
				map->grid[i][j] != WEST && map->grid[i][j] != '\n')
				return (print_error(ERR_INVALID_CHAR), false);
		}
	}
	return (true);
}

/**
 * Validate the map structure and contents
 * @param map Pointer to the game structure containing the map
 * @return true if the map is valid, false otherwise
 */

bool	validate_map(t_game *game)
{
	if ((validate_texture(game) == false) 
		|| (validate_color(&game->map) == false)
		|| (validate_char(&game->map) == false)
		|| (validate_player(game) == false)
		|| (validate_map_walls(game) == false))
		return (false);
	return (true);
}
