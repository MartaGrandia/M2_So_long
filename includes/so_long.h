/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrandia <mgrandia@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:02:10 by mgrandia          #+#    #+#             */
/*   Updated: 2025/06/07 17:40:17 by mgrandia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"
# include "MLX42/MLX42.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <memory.h> //LA NECECITO?
# include <fcntl.h>

# define TILE_SIZE 64

// Estructura para almacenar las texturas

typedef struct s_textures
{
	mlx_texture_t	*wall;
	mlx_texture_t	*floor;
	mlx_texture_t	*collect;
	mlx_texture_t	*exit;
	mlx_texture_t	*player;
}	t_textures;

// Estructura principal del juego

typedef struct s_game
{
	mlx_t		*mlx;
	char		**map;
	int			map_width;
	int			map_height;
	t_textures	textures;
	mlx_image_t	**images;
	int			player_x;
	int			player_y;
	int			collect;
	int			moves;
}	t_game;

// Funciones principales
int		load_textures(t_game *game);
int		convert_textures_to_images(t_game *game);
void	draw_map(t_game *game);
int		init_game(t_game *game, char **map, int map_height);
void	cleanup_textures(t_game *game);
void	key_handler(mlx_key_data_t keydata, void *param);
void	print_map_debug(char **map, int height);
// Funciones de validación (que ya deberías tener)
char	**parse_and_validate_map(char *filename);
int		validate_map(char **map);

// Funciones de movimiento (para implementar después)
void	move_player(t_game *game, int dx, int dy);
int		is_valid_move(t_game *game, int x, int y);

//-------------------------------marta
int		error_texture(void);
int		print_map_error(int error_code);
void	print_map(char **map);
void	*ft_free(void *ptr);
char	**free_map(char **mapa, int line_count, char *line, int fd);
char	**read_map(const char *ruta, int *filas);
void	free_normal_map(char **map);

//------------utils--------------
void	find_player(char **map, int *x, int *y);

//--------------map_validate-----------------
int		validate_map_elements(char **map);
int		count_colec(char **map);
void	flood_fill(char **mapa, int x, int y, int alto);
int		is_rectangular_map(char **map, int filas);
int		check_walls_border(char **map, int filas);
//------------------------------------
#endif
