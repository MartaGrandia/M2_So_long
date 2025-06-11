/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrandia <mgrandia@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:30:11 by mgrandia          #+#    #+#             */
/*   Updated: 2025/06/07 17:41:56 by mgrandia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// Maneja la lógica del mov del jugador segun la new posición y el tipo de tile.
// Verif. que la newa posición esté dentro del mapa y que no sea un ('1').
// Si tile == coleccionable ('C'), contador--  y cambia el tile a suelo ('0')
// Si el tile es ('E'), solo permite cerrar la ventana(ganar) si colect = 0
// Retorna 1 si el movimiento es válido y puede realizarse, 0 en caso contrario.
static int	handle_mov_logic(t_game *game, int new_x, int new_y, int new_tile)
{
	if (new_x < 0 || new_x >= game->map_width
		|| new_y < 0 || new_y >= game->map_height)
		return (0);
	if (new_tile == '1')
		return (0);
	if (new_tile == 'C')
	{
		game->collect--;
		game->map[new_y][new_x] = '0';
	}
	if (new_tile == 'E')
	{
		if (game->collect == 0)
		{
			mlx_close_window(game->mlx);
			return (1);
		}
		else
			return (0);
	}
	return (1);
}

// Aplica el movimiento actualizando la posición del jugador en el mapa,
// actualiza el contador de movimientos, y redibuja el mapa completo.
// Cambia la posición anterior del jugador a ('0')  y la nueva a ('P').
static void	apply_movement_and_draw(t_game *game, int new_x, int new_y)
{
	game->map[game->player_y][game->player_x] = '0';
	game->player_x = new_x;
	game->player_y = new_y;
	game->map[new_y][new_x] = 'P';
	game->moves++;
	draw_map(game);
	ft_printf("Movement: %d\n", game->moves);
}

// Calcula la nueva posición del jugador sumando el desplazamiento (dx, dy).
// Obtiene el tile en la nueva posición y verifica si el movimiento es válido.
// Si es válido, actualiza la posición y redibuja el mapa.
static void	move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;
	int	new_tile;

	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	new_tile = game->map[new_y][new_x];
	if (handle_mov_logic(game, new_x, new_y, new_tile))
		apply_movement_and_draw(game, new_x, new_y);
}

// Manejador básico de eventos de teclado.
// Detecta las teclas W, A, S, D para mover al jugador 
// También cierra la ventana si se presiona Escape.
// Actualiza el contador de coleccionables antes de cada movimiento.
void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	game->collect = count_colec(game->map);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		move_player(game, 0, -1);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		move_player(game, 0, 1);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		move_player(game, 1, 0);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		move_player(game, -1, 0);
}
