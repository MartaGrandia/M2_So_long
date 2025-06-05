/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrandia <mgrandia@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:02:10 by mgrandia          #+#    #+#             */
/*   Updated: 2025/05/31 17:17:15 by mgrandia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	validate_map_elements(char **map)
{
	int	fil;
	int	col;
	int	count_p;
	int	count_e;

	fil = 0;
	count_p = 0;
	count_e = 0;
	while (map[fil])
	{
		col = 0;
		while (map[fil][col])
		{
			if (map[fil][col] == 'P')
				count_p++;
			if (map[fil][col] == 'E')
				count_e++;
			col ++;
		}
		fil++;
	}
	if (count_p != 1 || count_e != 1)
		return (0);
	return (1);
}

int	count_colec(char **map)
{
	int	fil;
	int	col;
	int	count_c;

	fil = 0;
	count_c = 0;
	while (map[fil])
	{
		col = 0;
		while (map[fil][col])
		{
			if (map[fil][col] == 'C')
				count_c++;
			col ++;
		}
		fil++;
	}
	return (count_c);
}

void	flood_fill(char **mapa, int x, int y, int alto)
{
	int	ancho;

	ancho = ft_strlen(mapa[0]);
	if (x < 0 || y < 0 || x >= ancho || y >= alto)
		return ;
	if (mapa[y][x] == '1' || mapa[y][x] == 'V')
		return ;
	mapa[y][x] = 'V';
	flood_fill(mapa, x + 1, y, alto);
	flood_fill(mapa, x - 1, y, alto);
	flood_fill(mapa, x, y + 1, alto);
	flood_fill(mapa, x, y - 1, alto);
}
