/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukibrok <mukibrok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:51:23 by mukibrok          #+#    #+#             */
/*   Updated: 2025/08/19 19:52:54 by mukibrok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_mandatory/cub3d.h"

static int	count_elems(char **v)
{
	int	i;

	i = 0;
	while (v && v[i])
		i++;
	return (i);
}

static void	strip_trailing_nl(char *s)
{
	size_t	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	if (len && s[len - 1] == '\n')
		s[len - 1] = '\0';
}

static int	is_number(const char *s)
{
	int	i;

	if (!s || !*s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (!ft_isdigit((unsigned char)s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	extract_texture_path(t_game *game, char **tex_path, char **split_line)
{
	int	n;

	n = count_elems(split_line);
	if (n >= 1)
		strip_trailing_nl(split_line[n - 1]);
	if (n != 2 || *tex_path != NULL)
	{
		free_string_array(split_line);
		handle_parsing_error(game,
			"Error\nInvalid or duplicate texture definition\n");
	}
	*tex_path = ft_strdup(split_line[1]);
	if (!*tex_path)
	{
		free_string_array(split_line);
		handle_parsing_error(game,
			"Error\nMemory allocation failed for texture path\n");
	}
	strip_trailing_nl(*tex_path);
	free_string_array(split_line);
}

int	validate_rgb_line_format(char *rgb_line)
{
	int	i;
	int	commas;

	if (!rgb_line)
		return (0);
	strip_trailing_nl(rgb_line);
	if (!ft_isdigit((unsigned char)rgb_line[0]))
		return (0);
	i = 0;
	commas = 0;
	while (rgb_line[i])
	{
		if (rgb_line[i] == ',')
		{
			commas++;
			if (rgb_line[i + 1] == ',' || rgb_line[i + 1] == '\0')
				return (0);
		}
		else if (!ft_isdigit((unsigned char)rgb_line[i]))
			return (0);
		i++;
	}
	return (commas == 2);
}

int	parse_and_validate_rgb_values(int *rgb, char *rgb_line)
{
	char	**parts;
	int		n;
	int		i;
	int		val;

	if (!validate_rgb_line_format(rgb_line))
		return (0);
	parts = ft_split(rgb_line, ',');
	if (!parts)
		return (0);
	n = count_elems(parts);
	if (n != 3)
		return (free_string_array(parts), 0);
	i = 0;
	while (i < 3)
	{
		strip_trailing_nl(parts[i]);
		if (!is_number(parts[i]))
			return (free_string_array(parts), 0);
		val = ft_atoi(parts[i]);
		if (val < 0 || val > 255)
			return (free_string_array(parts), 0);
		rgb[i] = val;
		i++;
	}
	return (free_string_array(parts), 1);
}

void	extract_rgb_colors(t_game *game, int *rgb, char **split_line)
{
	int	n;

	n = count_elems(split_line);
	if (n >= 1)
		strip_trailing_nl(split_line[n - 1]);
	if (n != 2)
	{
		free_string_array(split_line);
		handle_parsing_error(game, "Error\nInvalid color definition format\n");
	}
	if (!parse_and_validate_rgb_values(rgb, split_line[1]))
	{
		free_string_array(split_line);
		handle_parsing_error(game,
			"Error\nInvalid RGB color values (must be 0-255)\n");
	}
	free_string_array(split_line);
}
