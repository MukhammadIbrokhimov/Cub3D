/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_statistics.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukibrok <mukibrok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:48:57 by mukibrok          #+#    #+#             */
/*   Updated: 2025/08/19 19:48:59 by mukibrok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_mandatory/cub3d.h"

/**
 * @brief Set player position and initial direction vectors
 */

void	set_player_position_and_direction(t_game *game, char direction,
		int row, int col)
{
	game->player.pos_y = (double)row;
	game->player.pos_x = (double)col;
	game->player.initial_dir = direction;
	if (direction == 'N')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = -1.0;
	}
	else if (direction == 'S')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = 1.0;
	}
	else if (direction == 'W')
	{
		game->player.dir_x = -1.0;
		game->player.dir_y = 0.0;
	}
	else if (direction == 'E')
	{
		game->player.dir_x = 1.0;
		game->player.dir_y = 0.0;
	}
}

int	scan_row(t_game *g, char *row, int r, int base, int *pc)
{
	int	c;

	c = 0;
	while (row[c])
	{
		if (is_character_valid(row[c], "NSEW"))
		{
			set_player_position_and_direction(g, row[c], r, base + c);
			(*pc)++;
		}
		c++;
	}
	return (c);
}

void	calculate_map_dimensions(t_game *game, char **map, int srow, int scol)
{
	int	row;
	int	max_w;
	int	pc;
	int	w;

	row = srow;
	max_w = 0;
	pc = 0;
	while (map[row])
	{
		w = scan_row(game, map[row] + scol, row, scol, &pc);
		if (w > max_w)
			max_w = w;
		row++;
	}
	if (pc == 1)
		(game->map.width = max_w, game->map.height = row);
	else
		(game->map.width = 0, game->map.height = 0);
}

/**
 * @brief Validate that all required configuration elements are present
 */

void	validate_configuration_completeness(t_game *game)
{
	int	color_index;

	if (!game->textures.north.path || !game->textures.south.path ||
		!game->textures.west.path || !game->textures.east.path)
	{
		handle_parsing_error(game, "Error\nMissing texture definitions (NO/SO/WE/EA)\n");
	}
	color_index = 0;
	while (color_index < 3)
	{
		if (game->map.floor_rgb[color_index] == -1 || 
			game->map.ceiling_rgb[color_index] == -1)
		{
			handle_parsing_error(game, "Error\nMissing color definitions (F/C)\n");
		}
		color_index++;
	}
}

/**
 * @brief Extract configuration data from a single line
 */

int	extract_map_statistics(t_game *game, char *config_line)
{
	static int	elements_processed = 0;
	while (elements_processed < 6)
	{
		if (config_line[0] == ' ' && !config_line[1])
			return (0);
		if (!ft_strncmp(config_line, "NO ", 3))
			extract_texture_path(game, &game->textures.north.path, 
				ft_split(config_line, ' '));
		else if (!ft_strncmp(config_line, "SO ", 3))
			extract_texture_path(game, &game->textures.south.path, 
				ft_split(config_line, ' '));
		else if (!ft_strncmp(config_line, "WE ", 3))
			extract_texture_path(game, &game->textures.west.path, 
				ft_split(config_line, ' '));
		else if (!ft_strncmp(config_line, "EA ", 3))
			extract_texture_path(game, &game->textures.east.path, 
				ft_split(config_line, ' '));
		else if (!ft_strncmp(config_line, "F ", 2))
			extract_rgb_colors(game, game->map.floor_rgb, 
				ft_split(config_line, ' '));
		else if (!ft_strncmp(config_line, "C ", 2))
			extract_rgb_colors(game, game->map.ceiling_rgb, 
				ft_split(config_line, ' '));
		else
			handle_parsing_error(game, "Error\nInvalid configuration element\n");
		elements_processed++;
		return (0);
	}
	validate_configuration_completeness(game);
	return (1);
}
