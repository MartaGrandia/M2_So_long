/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrandia <mgrandia@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:02:10 by mgrandia          #+#    #+#             */
/*   Updated: 2025/06/07 12:57:14 by mgrandia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	process_map(char **map, char **map_2, int filas)
{
	int		num_colec;
	int		x;
	int		y;

	num_colec = count_colec(map);
	x = -1;
	y = -1;
	if (validate_map_elements(map) != 1 && num_colec == 0)
	{
		ft_printf("los elementos no estan bien\n");
		return (0);
	}
	find_player(map, &x, &y);
	flood_fill(map_2, x, y, filas);
	num_colec = count_colec(map_2);
	if (num_colec == 0)
		ft_printf("llega a todos los C\n");
	else
		ft_printf("No llega a todos los C\n");
	if (is_rectangular_map(map, filas) == 0)
		ft_printf("No es rectangular\n");
	else
		ft_printf("Es rectangular\n");
	if (check_walls_border(map, filas) == 0)
		ft_printf("No te paret a tot el borde\n");
	else
		ft_printf("Te paret a tot el borde\n");
	return (1);
}
//--------------------------------------------------------


// Función para inicializar el juego
int	init_game(t_game *game, char **map, int map_height)
{
    // Copiar el mapa
	game->map = map;
	game->map_height = map_height;
	game->map_width = ft_strlen(map[0]);
    
	ft_printf("Inicializando juego...\n");
	ft_printf("Dimensiones del mapa: %dx%d\n", game->map_width, game->map_height);
	ft_printf("Tamaño de ventana: %dx%d\n", 
	game->map_width * TILE_SIZE, game->map_height * TILE_SIZE);
    
    // Debug: mostrar el mapa
	print_map_debug(map, map_height);
    
    // Inicializar MLX
	game->mlx = mlx_init(game->map_width * TILE_SIZE, game->map_height * TILE_SIZE, "so_long",true);
	if (!game->mlx)
	{
		ft_printf("Error: No se pudo inicializar MLX\n");
		return (0);
	}
    
	ft_printf("MLX inicializado correctamente\n");
    
    // Cargar texturas
	ft_printf("Cargando texturas...\n");
	if (!load_textures(game))
	{
		ft_printf("Error al cargar texturas\n");
		return (0);
	}
	ft_printf("Texturas cargadas correctamente\n");
    
    // Convertir texturas a imágenes
	ft_printf("Convirtiendo texturas a imágenes...\n");
	if (!convert_textures_to_images(game))
	{
		ft_printf("Error al convertir texturas\n");
		return (0);
	}
	ft_printf("Texturas convertidas correctamente\n");
    
    // Dibujar el mapa inicial
	ft_printf("Dibujando mapa...\n");
	draw_map(game);
	ft_printf("Mapa dibujado correctamente\n");
    
	return (1);
}

// Función para limpiar memoria de texturas
void	cleanup_textures(t_game *game)
{
	if (game->textures.wall)
		mlx_delete_texture(game->textures.wall);
	if (game->textures.floor)
		mlx_delete_texture(game->textures.floor);
	if (game->textures.collectible)
		mlx_delete_texture(game->textures.collectible);
	if (game->textures.exit)
		mlx_delete_texture(game->textures.exit);
	if (game->textures.player)
		mlx_delete_texture(game->textures.player);
    
	if (game->images)
		free(game->images);
}

// Función de debug para verificar que el mapa se carga correctamente
void	print_map_debug(char **map, int height)
{
	int i;
       
	i = 0;
	ft_printf("=== DEBUG: Contenido del mapa ===\n");
	while (i < height)
	{
		ft_printf("Fila %d: %s\n", i, map[i]);
		i++;
	}
	ft_printf("=== Fin del mapa ===\n");
}

int main(int argc, char **argv)
{
    t_game game;
    char **map_original;
    char **map_copy;
    int filas = 0;

    if (argc != 2)
    {
        ft_printf("Uso: %s <mapa.ber>\n", argv[0]);
        return (1);
    }

    // Leer mapa original y copia (para validación o lo que uses)
    map_original = read_map(argv[1], &filas);
    map_copy = read_map(argv[1], &filas);

    if (!map_original || !map_copy)
    {
        ft_printf("Error: No se pudo leer el mapa\n");
        return (1);
    }

    // Validar o procesar el mapa con tu función
    if (!process_map(map_original, map_copy, filas))
    {
        ft_printf("Error: Mapa inválido\n");
        free_normal_map(map_original);
        free_normal_map(map_copy);
        return (1);
    }

    // Si el mapa es válido, inicializamos el juego con el mapa original
    if (!init_game(&game, map_original, filas))
    {
        ft_printf("Error: No se pudo inicializar el juego\n");
        free_normal_map(map_original);
        free_normal_map(map_copy);
        return (1);
    }

    // Liberar la copia ya que no se usará más
    free_normal_map(map_copy);

    // Hook para manejar teclas
    mlx_key_hook(game.mlx, key_handler, &game);

    // Iniciar el loop principal
    mlx_loop(game.mlx);

    // Limpiar recursos y memoria al terminar
    cleanup_textures(&game);
    mlx_terminate(game.mlx);
    free_normal_map(map_original);

    return (0);
}

// Ejemplo de handler para teclas (función básica)
void key_handler(mlx_key_data_t keydata, void *param)
{
    t_game *game = (t_game *)param;
    
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        mlx_close_window(game->mlx);
    
    // Aquí puedes agregar el movimiento del jugador
    // if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
    //     move_player(game, 0, -1);
}
