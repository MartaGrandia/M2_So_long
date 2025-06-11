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

//----------map_reader----------
char	**read_map(const char *ruta, int *filas);

//----------free_utils---------
void	cleanup_textures(t_game *game);
void	*ft_free(void *ptr);
char	**free_map(char **mapa, int line_count, char *line, int fd);
void	free_normal_map(char **map);

//----------error_msg---------
int		error_texture(int error_code);
int		print_map_error(int error_code);

//----------map_valid----------
int		validate_map_elements(char **map);
int		count_colec(char **map);
void	flood_fill(char **mapa, int x, int y, int alto);
int		is_rectangular_map(char **map, int filas);
int		check_walls_border(char **map, int filas);

//----------utils----------
void	find_player(char **map, int *x, int *y);
void	print_map_debug(char **map, int height);
void	print_map(char **map);

//----------draw_map----------
int		load_textures(t_game *game);
int		convert_textures_to_images(t_game *game);
void	draw_map(t_game *game);

//----------move_map----------
void	key_handler(mlx_key_data_t keydata, void *param);
#endif
