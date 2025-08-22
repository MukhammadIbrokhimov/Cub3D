/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukibrok <mukibrok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:49:35 by mukibrok          #+#    #+#             */
/*   Updated: 2025/08/19 19:50:51 by mukibrok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d.h"

/**
 * @brief Validate that the parsed map meets all requirements
 */

int	validate_parsed_map(t_game *game)
{
	if (!validate_map_walls(game))
	{
		ft_printf("Error\nMap is not properly enclosed by walls\n");
		return (0);
	}
	return (1);
}

/**
 * @brief Handle parsing errors with proper cleanup and messaging
 */

void	handle_parsing_error(t_game *game, char *error_message)
{
	ft_printf("%s", error_message);
	if (game->map.grid)
		free_string_array(game->map.grid);
	if (game->map.current_line)
		free(game->map.current_line);
	if (game->map.data_buffer)
		free(game->map.data_buffer);
	free_texture_paths(game);
	exit(EXIT_FAILURE);
}

/**
 * @brief Normalize map to rectangular format for easier processing
 */

void	normalize_map_dimensions(t_game *g)
{
	int	i;

	calculate_map_dimensions(g, g->map.grid, 0, 0);
	if (!g->map.height || !g->map.width)
		handle_parsing_error(g, ERR_INVALID_MAP);
	i = 0;
	while (g->map.grid[i])
	{
		if (get_string_length_no_newline(g->map.grid[i]) < g->map.width)
		{
			g->map.grid[i] = resize_string_to_size(g->map.grid[i], g->map.width);
			if (!g->map.grid[i])
				handle_parsing_error(g, ERR_MALLOC);
		}
		i++;
	}
}

/**
 * @brief Read and parse the entire map configuration file
 */

int	read_and_parse_map_file(int fd, t_game *g)
{
	char	*line;
	int		parsing;

	parsing = 0;
	while ((line = get_next_line(fd)))
	{
		if (line[0] == '\n')
			line[0] = ' ';
		if (!parsing)
			parsing = extract_map_statistics(g, line);
		if (parsing)
		{
			if (ft_strchr(line, '/'))
			{
				free(line);
				return (handle_parsing_error(g, ERR_INVALID_MAP), EXIT_FAILURE);
			}
			g->map.data_buffer = join_strings_with_separator(g->map.data_buffer, line);
		}
		free(line);
	}
	g->map.grid = ft_split(g->map.data_buffer ? g->map.data_buffer : "", '/');
	free(g->map.data_buffer);
	g->map.data_buffer = NULL;
	return (normalize_map_dimensions(g), EXIT_SUCCESS);
}

/**
 * @brief Main map file parsing function
 */

int	parse_map_file(t_game *game, int file_descriptor)
{
	read_and_parse_map_file(file_descriptor, game);
	if (!validate_parsed_map(game))
		return (0);
	close(file_descriptor);
	return (1);
}
