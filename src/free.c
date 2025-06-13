/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrandia <mgrandia@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 21:00:36 by mgrandia          #+#    #+#             */
/*   Updated: 2025/06/13 21:04:08 by mgrandia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	*ft_free(void *ptr)
{
	free(ptr);
	return (NULL);
}

// Libera la memoria del mapa en caso de error durante la lectura:
// - Libera cada línea del mapa hasta line_count
// - Libera la última línea leída
// - Cierra el descriptor de archivo
// - Devuelve NULL para señalizar error
char	**free_map(char **mapa, int line_count, char *line, int fd)
{
	int	i;

	i = 0;
	while (i < line_count)
	{
		free (mapa[i]);
		i ++;
	}
	free (mapa);
	free (line);
	close (fd);
	return (NULL);
}

// Libera completamente un mapa bidimensional (array de strings):
// - Libera cada línea individual
// - Libera el array principal
void	free_normal_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map && map[i])
	{
		free(map[i]);
		i ++;
	}
	free (map);
}
