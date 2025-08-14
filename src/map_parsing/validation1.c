/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukibrok <mukibrok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 01:39:51 by mukibrok          #+#    #+#             */
/*   Updated: 2025/08/14 13:54:11 by mukibrok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

/**
 * Validate the player position in the map
 * Checks if there is exactly one player in the map and sets the player's position and direction
 * @param map Pointer to the game structure containing the map
 * @return true if the player is valid, false otherwise
 */

bool	validate_player(t_map *map)
{
	int	i;
	int	j;
	int	player_count;

	i = -1;
	player_count = 0;
	while (++i < map->height && map->grid[i])
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (map->grid[i][j] == NORTH || map->grid[i][j] == SOUTH ||
				map->grid[i][j] == EAST || map->grid[i][j] == WEST)
			{
				player_count++;
				if (player_count > 1)
					return (print_error(ERR_MULTI_PLAYER), false);
				map->player.pos_x = j + 0.5;
				map->player.pos_y = i + 0.5;
				map->player.initial_dir = map->grid[i][j];
			}
			j++;
		}
	}
	if (player_count == 0)
		return (print_error(ERR_NO_PLAYER), false);
	return (true);
}

/**
 * Validate the map structure
 * Checks if the map is rectangular, has valid characters, and is closed
 * @param game Pointer to the game structure containing the map
 * @return true if the map is valid, false otherwise
 */

bool	validate_map_walls(t_map *game)
{
	char	**temp_map;
	bool		result;

	temp_map = create_temp_map(game);
	if (!temp_map)
		return (false);
	result = flood_fill(temp_map, (int)game->player.pos_y, (int)game->player.pos_x, game);
	free_double_ptr(temp_map);
	if (!result)
		return (print_error(ERR_MAP_NOT_CLOSED), false);
	return (true);
}

/**
 * Create a temporary copy of the map for flood fill
 * Normalize all lines to the same width (pad with spaces)
 */

char	**create_temp_map(t_map *game)
{
	char	**temp_map;
	int		i = 0;
	int		j;

	temp_map = malloc(sizeof(char*) * (game->height + 1));
	if (!temp_map)
		return (NULL);
	while (i < game->height)
	{
		temp_map[i] = malloc(sizeof(char) * (game->width + 1));
		if (!temp_map[i])
		{
			while (--i >= 0)
				free(temp_map[i]);
			free(temp_map);
			return (NULL);
		}
		j = 0;
		while (j < game->width)
		{
			if (j < (int)ft_strlen(game->grid[i]) && game->grid[i][j] != '\n')
				temp_map[i][j] = game->grid[i][j];
			else
				temp_map[i][j] = SPACE;
			j++;
		}
		temp_map[i][game->width] = '\0';
		i++;
	}
	temp_map[game->height] = NULL;
	return (temp_map);
}

/**
 * Flood fill algorithm to check wall closure
 * Returns 0 if any empty space reaches the border
 */

int	flood_fill(char **map, int y, int x, t_map *game)
{
	/* Check bounds */
	if (y < 0 || y >= game->height || x < 0 || x >= game->width)
		return (0); /* Reached border - map not closed */

	/* If we hit a wall or already visited, stop */
	if (map[y][x] == WALL || map[y][x] == 'X')
		return (1);

	/* If we hit a space at the border, map is not closed */
	if (map[y][x] == SPACE && (y == 0 || y == game->height - 1 || 
		x == 0 || x == game->width - 1))
		return (0);

	/* Mark as visited */
	map[y][x] = 'X';

	/* Recursively check all 4 directions */
	if (!flood_fill(map, y - 1, x, game) ||	/* Up */
		!flood_fill(map, y + 1, x, game) ||	/* Down */
		!flood_fill(map, y, x - 1, game) ||	/* Left */
		!flood_fill(map, y, x + 1, game))		/* Right */
		return (0);
	return (1);
}