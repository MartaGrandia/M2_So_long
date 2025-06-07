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

void	move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;
	int	new_tile;

	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	new_tile = game->map[new_y][new_x];
	if (new_x < 0 || new_x >= game->map_width
		|| new_y < 0 || new_y >= game->map_height)
		return ;
	if (new_tile == '1')
		return ;
	if (new_tile == 'C')
	{
		game->collect--;
		game->map[new_y][new_x] = '0';
	}
	if (new_tile == 'E')
	{
		if (game->collect == 0)
		{
			ft_printf("HAS GANADO!!");
			mlx_close_window(game->mlx);
			return ;
		}
		else
			return ;
	}
	game->map[game->player_y][game->player_x] = '0';
	game->player_x = new_x;
	game->player_y = new_y;
	game->map[new_y][new_x] = 'P';
	game->moves++;
	draw_map(game);
	ft_printf("Movimiento: %d\n", game->moves);
}

// Ejemplo de handler para teclas (función básica)
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
