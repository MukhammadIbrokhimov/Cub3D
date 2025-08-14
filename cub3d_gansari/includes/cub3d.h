/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukibrok <mukibrok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:25:55 by gansari           #+#    #+#             */
/*   Updated: 2025/08/14 19:26:25 by mukibrok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ************************************************************************** */
/*                               INCLUDES                                     */
/* ************************************************************************** */

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stddef.h>
# include <mlx.h>
# include <math.h>
# include <limits.h>
# include <stdbool.h>
# include <stdint.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "keys.h"
# include "game_struct.h"
# include "../Libft/libft.h"
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

/* ************************************************************************** */
/*                               CONSTANTS                                    */
/* ************************************************************************** */

/* Window and display settings */
# define DEFAULT_WIDTH	1940	/* Default window width */
# define DEFAULT_HEIGHT	1280	/* Default window height */
# define TEXTURE_SIZE	128		/* Size of wall textures (128x128) */

/* Movement and rotation speeds */
# define MOVE_SPEED		0.09	/* Player movement speed */
# define ROTATION_SPEED	0.09	/* Player rotation speed */

/* Minimap settings */
# define MINIMAP_SCALE	7		/* Scale factor for minimap */
# define MINIMAP_OFFSET	10		/* Offset from window edge */

/* Colors for minimap and UI */
# define COLOR_BLACK	0x000000	/* Black color */
# define COLOR_WHITE	0xFFFFFF	/* White color */
# define COLOR_PLAYER	0xEEEE20	/* Player color on minimap */
# define COLOR_WALL		0x050505	/* Wall color on minimap */

/* ************************************************************************** */
/*                               ENUMERATIONS                                 */
/* ************************************************************************** */



/* ************************************************************************** */
/*                           FUNCTION PROTOTYPES                             */
/* ************************************************************************** */

/* ========================================================================== */
/*                               MAIN FUNCTIONS                              */
/* ========================================================================== */

void	init_game_structure(t_game *game);

/* ========================================================================== */
/*                            MEMORY MANAGEMENT                              */
/* ========================================================================== */

void	destroy_mlx_images(t_game *game);
void	cleanup_mlx_resources(t_game *game);
void	free_texture_paths(t_game *game);
void	free_string_array(char **array);
int		clean_exit_program(t_game *game);
void	cleanup_map(t_map *map);

/* ========================================================================== */
/*                            PARSING FUNCTIONS                              */
/* ========================================================================== */

int		parse_file(t_game *map, char *filename);
int		parse_map_line(char *line, t_map *map, int fd);
int		parse_texture(char *line, t_game *map);
int		parse_width(t_map *map);
t_color	parse_color(char *line);

/* ========================================================================== */
/*                            PARSING UTILITIES                              */
/* ========================================================================== */
int		split_len(char **split);
int		free_double_ptr(char **ptr);
int		space_count(char *line);
int		flood_fill(char **map, int y, int x, t_map *game);
void	print_map(t_map *map);
void	print_error(char *message);
char	**create_temp_map(t_map *game);

/* ========================================================================== */
/*                           VALIDATION                                  */
/* ========================================================================== */

bool	validate_texture(t_game *map);
bool	validate_color(t_map *map);
bool	validate_map(t_game *map);
bool	validate_file_extension(char *filename);
bool	validate_player(t_game *game);
bool	validate_char(t_map *map);
bool	validate_map_walls(t_game *game);
/* ========================================================================== */
/*                          MAP STATISTICS                                   */
/* ========================================================================== */

void	set_player_position_and_direction(t_game *game, char direction, int row, int col);
void	calculate_map_dimensions(t_game *game, char **map_array, int start_row, int start_col);
int		extract_map_statistics(t_game *game, char *config_line);

/* ========================================================================== */
/*                        RGB AND TEXTURE PARSING                           */
/* ========================================================================== */

void	extract_texture_path(t_game *game, char **texture_path, char **split_line);
int		validate_rgb_line_format(char *rgb_line);
void	extract_rgb_colors(t_game *game, int *rgb_array, char **split_line);

/* ========================================================================== */
/*                             GAME INITIALIZATION                           */
/* ========================================================================== */

void	handle_game_error(t_game *game, char *error_message);
void	init_game_settings(t_game *game);
void	init_mlx_images(t_game *game);
int		init_game_engine(t_game *game);

/* ========================================================================== */
/*                           INPUT HANDLING                                  */
/* ========================================================================== */

int		handle_keyboard_input(int keycode, t_game *game);
int		handle_mouse_rotation(int mouse_x, int mouse_y, t_game *game);

/* ========================================================================== */
/*                           PLAYER MOVEMENT                                 */
/* ========================================================================== */

void	move_player_with_collision(t_game *game, double delta_x, double delta_y, char direction_sign);
void	rotate_player_view(t_game *game, double rotation_speed);

/* ========================================================================== */
/*                            RAYCASTING ENGINE                              */
/* ========================================================================== */

void	calculate_delta_distances(t_game *game);
void	calculate_step_and_side_distances(t_game *game);
void	execute_dda_algorithm(t_game *game);
void	init_raycasting_for_column(t_game *game, int screen_x);
void	execute_raycasting(t_game *game);

/* ========================================================================== */
/*                            RENDERING UTILITIES                            */
/* ========================================================================== */

int		get_texture_color(t_game *game, int tex_x, int tex_y, int texture_index);

/* ========================================================================== */
/*                              DRAWING FUNCTIONS                            */
/* ========================================================================== */

void	put_pixel_to_image(t_game *game, int x, int y, int color);
void	draw_wall_column(t_game *game, int screen_x);
int		render_frame(t_game *game);

/* ========================================================================== */
/*                           BACKGROUND RENDERING                            */
/* ========================================================================== */

int		create_trgb_color(int transparency, int red, int green, int blue);
void	render_background_colors(t_game *game);

/* ========================================================================== */
/*                              MINIMAP FUNCTIONS (BONUS)                   */
/* ========================================================================== */

#ifdef BONUS
void	init_minimap_system(t_game *game);
void	draw_minimap_display(t_game *game);
void	update_minimap_player_position(t_game *game, int previous_x, int previous_y);
void	put_pixel_to_minimap(t_game *game, int x, int y, int color);
void	draw_minimap_case(t_game *game, int x, int y, int color);
#endif

#endif