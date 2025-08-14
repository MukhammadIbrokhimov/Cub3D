/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukibrok <mukibrok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 00:32:21 by mukibrok          #+#    #+#             */
/*   Updated: 2025/08/14 17:16:15 by mukibrok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * Count the number of elements in a double pointer array
 * @param split Double pointer array to count
 * @return Number of elements in the array
 */

int	split_len(char **split)
{
	int	count;

	count = 0;
	while (split[count])
		count++;
	return (count);
}

/**
 * Count the number of spaces in a line
 * @param line Pointer to the string to count spaces in
 * @return Number of spaces in the string
 */

int	space_count(char *line)
{
	int	count;

	count = 1;
	while (*line)
	{
		if (ft_isspace(*line))
			count++;
		line++;
	}
	return (count);
}

/**
 * Free a double pointer array
 * @param ptr Double pointer array to free
 * @return EXIT_SUCCESS if successful, EXIT_FAILURE if ptr is NULL
 */

int	free_double_ptr(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return (EXIT_FAILURE);
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (EXIT_SUCCESS);
}

