/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrandia <mgrandia@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:02:10 by mgrandia          #+#    #+#             */
/*   Updated: 2025/06/07 13:00:29 by mgrandia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	find_player(char **map, int *x, int *y)
{
	int	fil;
	int	col;

	fil = 0;
	while (map[fil])
	{
		col = 0;
		while (map[fil][col])
		{
			if (map[fil][col] == 'P')
			{
				*x = col;
				*y = fil;
				return ;
			}
			col ++;
		}
		fil++;
	}
}

// Función de debug para verificar que el mapa se carga correctamente
void	print_map_debug(char **map, int height)
{
	int	i;

	i = 0;
	ft_printf("=== DEBUG: Map content ===\n");
	while (i < height)
	{
		ft_printf("ROW %d: %s\n", i, map[i]);
		i++;
	}
	ft_printf("=== End of map ===\n");
}

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
