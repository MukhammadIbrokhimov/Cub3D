/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukibrok <mukibrok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 00:22:05 by mukibrok          #+#    #+#             */
/*   Updated: 2025/08/12 23:04:47 by mukibrok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

bool	validate_file_extension(char *filename)
{
	char	*ext;
	size_t		len;
	size_t		ext_len;

	ext = ".cub";
	len = ft_strlen(filename);
	ext_len = ft_strlen(ext);
	if (len < ext_len)
		return (false);
	return (ft_strcmp(filename + len - ext_len, ext) == 0);
}