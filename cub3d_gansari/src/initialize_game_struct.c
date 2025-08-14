/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_game_struct.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukibrok <mukibrok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:04:12 by gansari           #+#    #+#             */
/*   Updated: 2025/08/14 17:46:53 by mukibrok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_mlx(t_game *game)
{
	game->mlx.instance = NULL;
	game->mlx.window = NULL;
	game->mlx.width = 0;
	game->mlx.height = 0;
}

static void	init_map(t_game *game)
{
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->map.ceiling_color = (t_color){-1, -1, -1};
	game->map.floor_color = (t_color){-1, -1, -1};
}

static void	init_player(t_game *game)
{
	game->player.pos_x = 0.0;
	game->player.pos_y = 0.0;
	game->player.dir_x = 0.0;
	game->player.dir_y = 0.0;
	game->player.plane_x = 0.0;
	game->player.plane_y = 0.0;
	game->player.initial_dir = '\0';
	game->player.move_speed = 0.0;
	game->player.rotate_speed = 0.0;
}

static void	init_textures(t_game *game)
{
	game->textures.north.mlx_ptr = NULL;
	game->textures.north.path = NULL;
	game->textures.south.mlx_ptr = NULL;
	game->textures.south.path = NULL;
	game->textures.east.mlx_ptr = NULL;
	game->textures.east.path = NULL;
	game->textures.west.mlx_ptr = NULL;
	game->textures.west.path = NULL;
	game->textures.screen.mlx_ptr = NULL;
	game->textures.screen.path = NULL;
	#ifdef BONUS
	game->textures.minimap.mlx_ptr = NULL;
	#endif
}

void	init_game_structure(t_game *game)
{
	init_mlx(game);
	init_map(game);
	init_player(game);
	init_textures(game);
}
