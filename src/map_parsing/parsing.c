/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukibrok <mukibrok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 23:59:49 by mukibrok          #+#    #+#             */
/*   Updated: 2025/08/12 18:33:52 by mukibrok         ###   ########.fr       */
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

int	parse_file(t_game *map, char *filename)
{
	int		fd;
	char	*line;
	int		map_started;
	char	**temp_map;

	line = NULL;
	temp_map = NULL;
	map_started = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		print_error("Error opening file");
		return (EXIT_FAILURE);
	}
	line = get_next_line(fd);
	printf("Parsing file: %s\n", filename);
	printf("Reading lines...\n%s", line);
	while (line)
	{
		printf("%s", line);
		if (!map_started && (ft_strlen(line) == 0 || line[0] == '\n'))
			continue;
		if (ft_strncmp(line, "NO ", 3) == 0)
			map->textures[NORTH_TEX] = ft_strdup(line + 3);
		else if (strncmp(line, "SO ", 3) == 0)
			map->textures[SOUTH_TEX] = ft_strdup(line + 3);
		else if (strncmp(line, "WE ", 3) == 0)
			map->textures[2] = ft_strdup(line + 3);
		else if (strncmp(line, "EA ", 3) == 0)
			map->textures[3] = ft_strdup(line + 3);
		if (line[0] == 'F')
			map->floor_color = parse_color(line);
		if (line[0] == 'C')
			map->ceiling_color = parse_color(line);
		if (!map_started && (line[0] == '0' || line[0] == '1' || line[0] == ' '))
		{
			map_started = 1;
			if (!parse_map_line(line, map, fd))
			{
				print_error("Invalid parse map");
				free(line);
				close(fd);
				return (EXIT_FAILURE);
			}
		}
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
			break;
	}
	printf("Finished parsing file: %s\n", filename);
	return (EXIT_SUCCESS);
}

int	parse_map_line(char *line, t_game *map, int fd)
{
	char	**map_lines = NULL;
	int		map_line_count = 0;

	map_lines = malloc(sizeof(char *) * (MAX_MAP_LINES + 1)); // You may want to define a proper limit or dynamically grow
	if (!map_lines)
		return (EXIT_FAILURE);

	map_lines[map_line_count++] = ft_strdup(line); // Add the current line

	while ((line = get_next_line(fd)))
	{
		if (ft_strlen(line) == 0 || line[0] == '\n')
		{
			free(line);
			break;
		}
		map_lines[map_line_count++] = ft_strdup(line);
		free(line);
	}

	map_lines[map_line_count] = NULL; // Null-terminate array

	map->map = map_lines; // Or whatever your map struct uses
	map->map_height = map_line_count;
	map->map_width = ft_strlen(map_lines[0]); // Assuming all lines are of equal

	return (EXIT_SUCCESS); // Success
}
