/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrandia <mgrandia@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:53:03 by mgrandia          #+#    #+#             */
/*   Updated: 2025/06/07 17:41:37 by mgrandia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// Función para cargar todas las texturas desde la carpeta assets
int	load_textures(t_game *game)
{
	game->textures.wall = mlx_load_png("assets/wall.png");
	if (!game->textures.wall)
		return (error_texture());
	game->textures.floor = mlx_load_png("assets/floor.png");
	if (!game->textures.floor)
		return (error_texture());
	game->textures.collect = mlx_load_png("assets/collectible.png");
	if (!game->textures.collect)
		return (error_texture());
	game->textures.exit = mlx_load_png("assets/exit.png");
	if (!game->textures.exit)
		return (error_texture());
	game->textures.player = mlx_load_png("assets/player.png");
	if (!game->textures.player)
		return (error_texture());
	game->textures.player = mlx_load_png("assets/player.png");
	return (1);
}

// Función para convertir texturas a imágenes
int	convert_textures_to_images(t_game *game)
{
	int	i;

	i = 0;
	game->images = malloc(sizeof(mlx_image_t *) * 5);
	if (!game->images)
		return (0);
	game->images[0] = mlx_texture_to_image(game->mlx, game->textures.wall);
	game->images[1] = mlx_texture_to_image(game->mlx, game->textures.floor);
	game->images[2] = mlx_texture_to_image(game->mlx, game->textures.collect);
	game->images[3] = mlx_texture_to_image(game->mlx, game->textures.exit);
	game->images[4] = mlx_texture_to_image(game->mlx, game->textures.player);
	while (i < 5)
	{
		if (!game->images[i])
		{
			ft_printf("Error: No se pudo convertir textura %d a imagen\n", i);
			return (0);
		}
		i ++;
	}
	return (1);
}

// Función para obtener la imagen correcta según el carácter del mapa
mlx_image_t	*get_image_for_char(t_game *game, char c)
{
	if (c == '1')
		return (game->images[0]);
	else if (c == '0')
		return (game->images[1]);
	else if (c == 'C')
		return (game->images[2]);
	else if (c == 'E')
		return (game->images[3]);
	else if (c == 'P')
		return (game->images[4]);
	return (game->images[1]);
}

// Función para dibujar el mapa completo
void	draw_map(t_game *game)
{
	int			x;
	int			y;
	mlx_image_t	*img;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] != '1')
			{
				if (mlx_image_to_window(game->mlx, game->images[1],
						x * TILE_SIZE, y * TILE_SIZE) < 0)
				{
					ft_printf("Error: No se pudo dibujar el suelo\n");
					return ;
				}
			}
			img = get_image_for_char(game, game->map[y][x]);
			if (mlx_image_to_window(game->mlx, img, x * TILE_SIZE,
					y * TILE_SIZE) < 0)
			{
				ft_printf("Error: No dibujar en posición (%d, %d)\n", x, y);
				return ;
			}
			if (game->map[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
			}
			x++;
		}
		y++;
	}
}
