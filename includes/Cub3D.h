/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukibrok <mukibrok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:16:18 by mukibrok          #+#    #+#             */
/*   Updated: 2025/08/14 12:24:57 by mukibrok         ###   ########.fr       */
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
	double		pos_x;				/* Current player X position */
	double		pos_y;				/* Current player Y position */
	double		dir_x;				/* Player direction vector X component */
	double		dir_y;				/* Player direction vector Y component */
	double		plane_x;			/* Camera plane X component (FOV) */
	double		plane_y;			/* Camera plane Y component (FOV) */
	char		initial_dir;		/* Initial player direction (N/S/E/W) */
	double		move_speed;			/* Player movement speed */
	double		rotate_speed;		/* Player rotation speed */
}	t_player;

/* Game data structure */
typedef struct s_map
{
	char		**map;
	int			map_width;
	int			map_height;
	char		*textures[TEX_COUNT];
	t_color		floor_color;
	t_color		ceiling_color;
	t_player	player;
}	t_map;

// parsing and initialization map
int		parse_file(t_map *map, char *filename);
int		parse_map_line(char *line, t_map *map, int fd);
int		parse_texture(char *line, t_map *map);
int		parse_width(t_map *map);
t_color	parse_color(char *line);

// validation
bool	validate_texture(t_map *map);
bool	validate_color(t_map *map);
bool	validate_map(t_map *map);
bool	validate_file_extension(char *filename);
bool	validate_player(t_map *map);
bool	validate_char(t_map *map);
bool	validate_map_walls(t_map *game);

// error handling
void	print_error(char *message);

// helper functions
int		split_len(char **split);
int		free_double_ptr(char **ptr);
int		space_count(char *line);
int	flood_fill(char **map, int y, int x, t_map *game);
void	print_map(t_map *map);
void	init_map(t_map *map);
char	**create_temp_map(t_map *game);

// cleanup functions
void	cleanup_map(t_map *map);

#endif