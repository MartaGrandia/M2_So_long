/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
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

void	flood_fill(char **mapa, int x, int y, int ancho, int alto)
{
	if (x < 0 || y < 0 || x >= ancho || y >= alto)
		return ;
	//TODO comprobaciones para que no se salga de la matriz
	if (mapa[y][x] == '1' || mapa[y][x] == 'V')
		return ;
	mapa[y][x] = 'V';
	flood_fill(mapa, x + 1, y, ancho, alto);
	flood_fill(mapa, x - 1, y, ancho, alto);
	flood_fill(mapa, x, y + 1, ancho, alto);
	flood_fill(mapa, x, y - 1, ancho, alto);
}

int	process_map(char **map, char **map_2, int filas)
{
	int		num_colec;
	int	x;
	int	y;

	num_colec = count_colec(map);
	x = -1;
	y = -1;
	
	if (validate_map_elements(map) != 1 && num_colec == 0)
	{
		ft_printf("mapa no valido\n");
		return (0);
	}
	find_player(map, &x, &y);
	flood_fill(map_2, x, y, ft_strlen(map[0]), filas);
	num_colec = count_colec(map_2);
	if (num_colec > 0)
		ft_printf("todo perfecto\n");
	else
		ft_printf("Error en el mapaaa\n");
	return (1);	
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

int32_t	main(void)
{
	int		filas;
	char	**mapa;
	char	**mapa_2;

	filas = 0;
	mapa = read_map("./maps/map1.ber", &filas);
	mapa_2 = read_map("./maps/map1.ber", &filas);
	if (!mapa || !mapa_2)
		return (1);
	if (!process_map(mapa, mapa_2, filas))
	{
		free_normal_map(mapa_2);
		free_normal_map(mapa);
		return (1);
	}
	print_map(mapa);
	ft_printf("\n\n");
	print_map(mapa_2);
	free_normal_map(mapa_2);
	free_normal_map(mapa);
	return (0);
}
