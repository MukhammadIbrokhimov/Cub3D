/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukibrok <mukibrok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:16:18 by mukibrok          #+#    #+#             */
/*   Updated: 2025/08/10 21:49:46 by mukibrok         ###   ########.fr       */
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

#endif