/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrandia <mgrandia@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:02:10 by mgrandia          #+#    #+#             */
/*   Updated: 2025/06/07 11:58:15 by mgrandia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		ft_printf("%s\n", map[i]);
		i ++;
	}
}

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
// Función para cargar todas las texturas desde la carpeta assets
int load_textures(t_game *game)
{
    game->textures.wall = mlx_load_png("assets/wall.png");
    if (!game->textures.wall)
    {
        ft_printf("Error: No se pudo cargar wall.png\n");
        return (0);
    }
    
    game->textures.floor = mlx_load_png("assets/floor.png");
    if (!game->textures.floor)
    {
        ft_printf("Error: No se pudo cargar floor.png\n");
        return (0);
    }
    
    game->textures.collectible = mlx_load_png("assets/collectible.png");
    if (!game->textures.collectible)
    {
        ft_printf("Error: No se pudo cargar collectible.png\n");
        return (0);
    }
    
    game->textures.exit = mlx_load_png("assets/exit.png");
    if (!game->textures.exit)
    {
        ft_printf("Error: No se pudo cargar exit.png\n");
        return (0);
    }
    
    game->textures.player = mlx_load_png("assets/player.png");
    if (!game->textures.player)
    {
        ft_printf("Error: No se pudo cargar player.png\n");
        return (0);
    }
    
    return (1);
}

// Función para convertir texturas a imágenes
int convert_textures_to_images(t_game *game)
{
    // Allocar memoria para el array de imágenes
    game->images = malloc(sizeof(mlx_image_t*) * 5);
    if (!game->images)
        return (0);
    
    // Convertir cada textura a imagen
    game->images[0] = mlx_texture_to_image(game->mlx, game->textures.wall);
    game->images[1] = mlx_texture_to_image(game->mlx, game->textures.floor);
    game->images[2] = mlx_texture_to_image(game->mlx, game->textures.collectible);
    game->images[3] = mlx_texture_to_image(game->mlx, game->textures.exit);
    game->images[4] = mlx_texture_to_image(game->mlx, game->textures.player);
    
    // Verificar que todas las conversiones fueron exitosas
    for (int i = 0; i < 5; i++)
    {
        if (!game->images[i])
        {
            ft_printf("Error: No se pudo convertir textura %d a imagen\n", i);
            return (0);
        }
    }
    
    return (1);
}

// Función para obtener la imagen correcta según el carácter del mapa
mlx_image_t *get_image_for_char(t_game *game, char c)
{
    if (c == '1')
        return (game->images[0]);  // Wall
    else if (c == '0')
        return (game->images[1]);  // Floor
    else if (c == 'C')
        return (game->images[2]);  // Collectible
    else if (c == 'E')
        return (game->images[3]);  // Exit
    else if (c == 'P')
        return (game->images[4]);  // Player
    return (game->images[1]);     // Default: floor
}

// Función para dibujar el mapa completo
void draw_map(t_game *game)
{
    int x, y;
    mlx_image_t *img;
    
    y = 0;
    while (y < game->map_height)
    {
        x = 0;
        while (x < game->map_width)
        {
            // Primero dibujar el suelo para todas las posiciones
            if (game->map[y][x] != '1')
            {
                if (mlx_image_to_window(game->mlx, game->images[1], 
                    x * TILE_SIZE, y * TILE_SIZE) < 0)
                {
                    ft_printf("Error: No se pudo dibujar el suelo\n");
                    return;
                }
            }
            
            // Luego dibujar el elemento específico
            img = get_image_for_char(game, game->map[y][x]);
            if (mlx_image_to_window(game->mlx, img, 
                x * TILE_SIZE, y * TILE_SIZE) < 0)
            {
                ft_printf("Error: No se pudo dibujar en posición (%d, %d)\n", x, y);
                return;
            }
            
            // Guardar posición del jugador
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

// Función para inicializar el juego
int init_game(t_game *game, char **map, int map_height)
{
    // Copiar el mapa
    game->map = map;
    game->map_height = map_height;
    game->map_width = ft_strlen(map[0]);
    
    ft_printf("Inicializando juego...\n");
    ft_printf("Dimensiones del mapa: %dx%d\n", game->map_width, game->map_height);
    ft_printf("Tamaño de ventana: %dx%d\n", 
              game->map_width * TILE_SIZE, 
              game->map_height * TILE_SIZE);
    
    // Debug: mostrar el mapa
    print_map_debug(map, map_height);
    
    // Inicializar MLX
    game->mlx = mlx_init(game->map_width * TILE_SIZE, 
                        game->map_height * TILE_SIZE, "so_long", true);
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
void cleanup_textures(t_game *game)
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
void print_map_debug(char **map, int height)
{
    int i = 0;
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
