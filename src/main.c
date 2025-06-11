/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrandia <mgrandia@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:02:10 by mgrandia          #+#    #+#             */
/*   Updated: 2025/06/09 19:18:44 by mgrandia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	process_map(char **map, char **map_2, int filas)
{
	int		num_colec;
	int		x;
	int		y;

	num_colec = count_colec(map);
	x = -1;
	y = -1;
	if (validate_map_elements(map) != 1 && num_colec == 0)
		return (print_map_error(1));
	find_player(map, &x, &y);
	flood_fill(map_2, x, y, filas);
	num_colec = count_colec(map_2);
	if (num_colec != 0)
		return (print_map_error(2));
	if (is_rectangular_map(map, filas) == 0)
		return (print_map_error(3));
	if (check_walls_border(map, filas) == 0)
		return (print_map_error(4));
	return (1);
}

// Función para inicializar el juego
static int	init_game(t_game *game, char **map, int map_height)
{
	game->map = map;
	game->map_height = map_height;
	game->map_width = ft_strlen(map[0]);
	game->mlx = mlx_init(game->map_width * TILE_SIZE,
			game->map_height * TILE_SIZE, "so_long", true);
	if (!game->mlx)
	{
		ft_printf("Error: Could not initialize MLX\n");
		return (0);
	}
	if (!load_textures(game))
	{
		ft_printf("Error: Failed to load textures\n");
		return (0);
	}
	if (!convert_textures_to_images(game))
	{
		ft_printf("Error: Failed to convert textures\n");
		return (0);
	}
	draw_map(game);
	return (1);
}

static void	init_game_struct(t_game *game)
{
	game->mlx = NULL;
	game->map = NULL;
	game->map_width = 0;
	game->map_height = 0;
	game->images = NULL;
	game->player_x = 0;
	game->player_y = 0;
	game->collect = 0;
	game->moves = 0;
}

static int	so_long(char **map_original, char **map_copy, int filas)
{
	t_game	game;

	if (!process_map(map_original, map_copy, filas))
	{
		free_normal_map(map_original);
		free_normal_map(map_copy);
		return (1);
	}
	init_game_struct(&game);
	if (!init_game(&game, map_original, filas))
	{
		ft_printf("Error: Could not initialize the game\n");
		free_normal_map(map_original);
		free_normal_map(map_copy);
		return (1);
	}
	free_normal_map(map_copy);
	mlx_key_hook(game.mlx, key_handler, &game);
	mlx_loop(game.mlx);
	cleanup_textures(&game);
	mlx_terminate(game.mlx);
	free_normal_map(map_original);
	return (0);
}

int	main(int argc, char **argv)
{
	char	**map_original;
	char	**map_copy;
	int		filas;

	if (argc != 2)
	{
		ft_printf("Usage: %s <mapa.ber>\n", argv[0]);
		return (1);
	}
	filas = 0;
	map_original = read_map(argv[1], &filas);
	if (map_original == NULL)
	{
		return (1);
	}
	map_copy = read_map(argv[1], &filas);
	if (!map_original || !map_copy)
	{
		ft_printf("Error: Could not read the map\n");
		return (1);
	}
	return (so_long(map_original, map_copy, filas));
}
