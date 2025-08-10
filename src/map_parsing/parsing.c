/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukibrok <mukibrok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 23:59:49 by mukibrok          #+#    #+#             */
/*   Updated: 2025/08/11 00:04:42 by mukibrok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/Cub3D.h"

t_color parse_color(char *line, t_game *map)
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
