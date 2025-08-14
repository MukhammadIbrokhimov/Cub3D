/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukibrok <mukibrok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:16:18 by mukibrok          #+#    #+#             */
/*   Updated: 2025/08/14 12:08:06 by mukibrok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <errno.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "./libft/libft.h"
# include "./minilibx-linux/mlx.h"

/* Map characters */
# define WALL '1'
# define EMPTY '0'
# define NORTH 'N'
# define SOUTH 'S'
# define EAST 'E'
# define WEST 'W'
# define SPACE ' '
# define MAX_MAP_LINES 1000

/* Error messages */
# define ERR_FILE_EXT "File must have .cub extension"
# define ERR_FILE_OPEN "Cannot open file"
# define ERR_MALLOC "Memory allocation failed"
# define ERR_INVALID "Invalid map"
# define ERR_NO_PLAYER "No player found in map"
# define ERR_MULTI_PLAYER "Multiple players found"
# define ERR_MAP_NOT_CLOSED "Map is not surrounded by walls"
# define ERR_INVALID_CHAR "Invalid character in map"
# define ERR_MISSING_TEXTURE "Missing texture path"
# define ERR_INVALID_COLOR "Invalid color format"

/* Color structure */
typedef struct s_color {
	int	red;
	int	green;
	int	blue;
} t_color;

/* Texture identifiers */
typedef enum e_texture_type
{
	NORTH_TEX,
	SOUTH_TEX,
	WEST_TEX,
	EAST_TEX,
	TEX_COUNT
}	t_texture_type;

/* Player structure */
typedef struct s_player
{
	double	x;
	double	y;
	char	direction;
} t_player;

/* Game data structure */
typedef struct s_game
{
	char		**map;
	int			map_width;
	int			map_height;
	char		*textures[TEX_COUNT];
	t_color		floor_color;
	t_color		ceiling_color;
	t_player	player;
}	t_game;

// parsing and initialization map
int		parse_file(t_game *map, char *filename);
int		parse_map_line(char *line, t_game *map, int fd);
int		parse_texture(char *line, t_game *map);
int		parse_width(t_game *map);
t_color	parse_color(char *line);

// validation
bool	validate_texture(t_game *map);
bool	validate_color(t_game *map);
bool	validate_map(t_game *map);
bool	validate_file_extension(char *filename);
bool	validate_player(t_game *map);
bool	validate_char(t_game *map);
bool	validate_map_walls(t_game *game);

// error handling
void	print_error(char *message);

// helper functions
int		split_len(char **split);
int		free_double_ptr(char **ptr);
int		space_count(char *line);
int	flood_fill(char **map, int y, int x, t_game *game);
void	print_map(t_game *map);
void	init_map(t_game *map);
char	**create_temp_map(t_game *game);

// cleanup functions
void	cleanup_map(t_game *map);

#endif