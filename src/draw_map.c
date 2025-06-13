/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrandia <mgrandia@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:53:03 by mgrandia          #+#    #+#             */
/*   Updated: 2025/06/13 19:47:05 by mgrandia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// Carga las texturas PNG necesarias para el juego desde la carpeta "assets".
// Asigna cada textura al campo correspondiente en la estructurai.
// En caso de fallo en la carga, imprime un error específico y retorna 0.
// Retorna 1 si todas las texturas se cargan correctamente.
int	load_textures(t_game *game)
{
	game->textures.wall = mlx_load_png("assets/wall.png");
	if (!game->textures.wall)
		return (free_textures_and_error(game, 1));
	game->textures.floor = mlx_load_png("assets/floor.png");
	if (!game->textures.floor)
		return (free_textures_and_error(game, 2));
	game->textures.collect = mlx_load_png("assets/collectible.png");
	if (!game->textures.collect)
		return (free_textures_and_error(game, 3));
	game->textures.exit = mlx_load_png("assets/exit.png");
	if (!game->textures.exit)
		return (free_textures_and_error(game, 4));
	game->textures.player = mlx_load_png("assets/player.png");
	if (!game->textures.player)
		return (free_textures_and_error(game, 5));
	return (1);
}

// Convierte las texturas en imágenes que pueden ser dibujadas en pantalla.
// Reserva memoria para un array de punteros a imágenes y asigna cada imagen.
// Si falla la asignación o conversión de alguna text, muestra error y ret 0.
// Retorna 1 si todas las texturas se convierten correctamente.
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
			ft_printf("Error: Could not convert texture %d to image\n", i);
			return (0);
		}
		i ++;
	}
	return (1);
}

// Devuelve la imagen correcta según el carácter del mapa recibido:
// '1' → pared (wall), '0' → suelo (floor), 'C' → coleccionable,
// 'E' → salida (exit), 'P' → jugador (player).
// Si el carácter no coincide, retorna la imagen de suelo por defecto.
static mlx_image_t	*get_image_for_char(t_game *game, char c)
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

// Dibuja un "tile" o casilla del mapa en la posición (x, y).
// Primero dibuja el floor luego la img correspondiente al carácter del mapa.
// Si falla al dibujar el suelo o la imagen, imprime un mensaje de error.
// Actualiza las coordenadas del jugador si el tile es la posición del jugador.
static void	draw_tile(t_game *game, int x, int y)
{
	mlx_image_t	*img;

	if (mlx_image_to_window(game->mlx, game->images[1],
			x * TILE_SIZE, y * TILE_SIZE) < 0)
	{
		ft_printf("Error: Could not draw floor\n");
		return ;
	}
	img = get_image_for_char(game, game->map[y][x]);
	if (mlx_image_to_window(game->mlx, img, x * TILE_SIZE,
			y * TILE_SIZE) < 0)
	{
		ft_printf("Error: Could not draw at position (%d, %d)\n", x, y);
		return ;
	}
	if (game->map[y][x] == 'P')
	{
		game->player_x = x;
		game->player_y = y;
	}
}

// Recorre todo el mapa y dibuja cada casilla usando draw_tile.
// Itera por filas y columnas según el tamaño del mapa almacenado en 'game'.
// Esta función es responsable de mostrar el mapa completo en la ventana.
void	draw_map(t_game *game)
{
	int			x;
	int			y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			draw_tile(game, x, y);
			x++;
		}
		y++;
	}
}
