/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrandia <mgrandia@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:02:10 by mgrandia          #+#    #+#             */
/*   Updated: 2025/06/07 17:40:56 by mgrandia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// Free la memoria asociada a las texturas cargadas y a las imágenes del juego:
// - Elimina cada textura si fue cargada
// - Libera el array de imágenes si existe
void	cleanup_textures(t_game *game)
{
	if (game->textures.wall)
		mlx_delete_texture(game->textures.wall);
	if (game->textures.floor)
		mlx_delete_texture(game->textures.floor);
	if (game->textures.collect)
		mlx_delete_texture(game->textures.collect);
	if (game->textures.exit)
		mlx_delete_texture(game->textures.exit);
	if (game->textures.player)
		mlx_delete_texture(game->textures.player);
	if (game->images)
		free(game->images);
}

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
