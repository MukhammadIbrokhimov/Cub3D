/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukibrok <mukibrok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:30:20 by gansari           #+#    #+#             */
/*   Updated: 2025/08/14 17:52:01 by mukibrok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./cub3d <map_file>\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (validate_file_extension(argv[1]) == false)
		return (print_error(ERR_FILE_EXT), EXIT_FAILURE);
	init_game_structure(&game);
	parse_file(&game, argv[1]);
	printf("Map width: %d, height: %d\n", game.map.width, game.map.height);
	for (int i = 0; i < game.map.height; i++)
	{
		printf("%s", game.map.grid[i]);
		if (game.map.grid[i] == NULL)
			return (print_error(ERR_INVALID), EXIT_FAILURE);
	}
	if (!(validate_map(&game)))
	{
		cleanup_map(&game.map);
		return(EXIT_FAILURE);
	}
	if (init_game_engine(&game) != 0)
	{
		printf("Error\nGame engine initialization failed\n");
		cleanup_map(&game.map);
		
		return (5);
	}
	return (0);
}
