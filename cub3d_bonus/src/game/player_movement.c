/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukibrok <mukibrok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:51:12 by gansari           #+#    #+#             */
/*   Updated: 2025/08/21 16:42:09 by mukibrok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	player_with_collision(t_game *game, double delta_x, double delta_y)
{
	int		previous_grid_x;
	int		previous_grid_y;
	double	new_x;
	double	new_y;

	previous_grid_x = (int)game->player.pos_x;
	previous_grid_y = (int)game->player.pos_y;
	new_x = game->player.pos_x + delta_x;
	if (game->map.grid[(int)game->player.pos_y][(int)new_x] != '1')
		game->player.pos_x = new_x;
	new_y = game->player.pos_y + delta_y;
	if (game->map.grid[(int)new_y][(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
	#ifdef BONUS
	if ((int)game->player.pos_x != previous_grid_x || 
		(int)game->player.pos_y != previous_grid_y)
	{
		update_minimap_player_position(game, previous_grid_x, previous_grid_y);
	}
	#else
	(void)previous_grid_x;
	(void)previous_grid_y;
	#endif
}

void	rotate_player_view(t_game *game, double rotation_speed)
{
	double	temp_dir_x;
	double	temp_plane_x;
	double	cos_rotation;
	double	sin_rotation;

	cos_rotation = cos(rotation_speed);
	sin_rotation = sin(rotation_speed);
	temp_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos_rotation - 
		game->player.dir_y * sin_rotation;
	game->player.dir_y = temp_dir_x * sin_rotation + 
		game->player.dir_y * cos_rotation;
	temp_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos_rotation - 
		game->player.plane_y * sin_rotation;
	game->player.plane_y = temp_plane_x * sin_rotation + 
		game->player.plane_y * cos_rotation;
}

int	init_game_engine(t_game *game)
{
	init_game_settings(game);
	game->mlx.instance = mlx_init();
	if (!game->mlx.instance)
		handle_game_error(game, "Error\nFailed to initialize MLX\n");
	game->mlx.window = mlx_new_window(game->mlx.instance, 
			game->mlx.width, game->mlx.height, "cub3D");
	if (!game->mlx.window)
		handle_game_error(game, "Error\nFailed to create game window\n");
	init_mlx_images(game);
	init_player_input(game);
	#ifdef BONUS
	init_minimap_system(game);
	#endif
	mlx_loop_hook(game->mlx.instance, &render_frame, game);
	mlx_hook(game->mlx.window, 2, 1L << 0, handle_key_press, game);
	mlx_hook(game->mlx.window, 3, 1L << 1, handle_key_release, game);
	mlx_hook(game->mlx.window, 17, 1L << 0, clean_exit_program, game);
	#ifdef BONUS
	mlx_hook(game->mlx.window, 6, 1L << 6, handle_mouse_rotation, game);
	#endif
	mlx_loop(game->mlx.instance);
	return (0);
}
