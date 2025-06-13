/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrandia <mgrandia@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:02:10 by mgrandia          #+#    #+#             */
/*   Updated: 2025/06/13 21:02:42 by mgrandia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// Libera las primeras 3 texturas (wall, floor, collect)
static void	free_basic_textures(t_game *game)
{
	if (game->textures.wall)
	{
		mlx_delete_texture(game->textures.wall);
		game->textures.wall = NULL;
	}
	if (game->textures.floor)
	{
		mlx_delete_texture(game->textures.floor);
		game->textures.floor = NULL;
	}
	if (game->textures.collect)
	{
		mlx_delete_texture(game->textures.collect);
		game->textures.collect = NULL;
	}
}

// Libera todas las texturas cargadas y retorna el código de error
int	free_textures_and_error(t_game *game, int err_code)
{
	free_basic_textures(game);
	if (game->textures.exit)
	{
		mlx_delete_texture(game->textures.exit);
		game->textures.exit = NULL;
	}
	if (game->textures.player)
	{
		mlx_delete_texture(game->textures.player);
		game->textures.player = NULL;
	}
	return (error_texture(err_code));
}

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
