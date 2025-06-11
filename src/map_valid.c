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

// Valida que el mapa contenga exactamente un jugador ('P') y una salida ('E').
// Recorre todo el mapa contando ocurrencias de 'P' y 'E'.
// Devuelve 1 si hay exactamente uno de cada uno, o 0 en caso contrario.
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

// Cuenta la cantidad total de coleccionables ('C') en el mapa.
// Recorre todo el mapa sumando las ocurrencias de 'C'.
// Devuelve el número total de coleccionables encontrados.
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

// Realiza un algoritmo para marcar las posiciones accesibles desde (x, y).
// Marca con 'V' las celdas visitadas que no sean paredes ('1') ni ('V').
// Sirve para comprobar la accesibilidad de las áreas del mapa.
// Parámetros: mapa, coordenadas x e y, y la altura del mapa (número de filas).
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

// Comprueba si el mapa es rectangular.
// Compara la longitud de cada fila con la anterior.
// Devuelve 1 si todas las filas tienen la misma longitud, 0 si alguna difiere.
int	is_rectangular_map(char **map, int filas)
{
	if (filas <= 1)
		return (1);
	while (filas > 1)
	{
		if (ft_strlen(map[filas - 1]) == ft_strlen(map[filas - 2]))
			filas --;
		else
			return (0);
	}
	return (1);
}

// Verifica que el borde del mapa esté completamente rodeado por paredes ('1').
// Comprueba la primera y última fila, y la primera y última columna.
// Devuelve 1 si todas las posiciones del borde son paredes, 0 si no.
int	check_walls_border(char **map, int filas)
{
	int	ancho;
	int	i;

	ancho = ft_strlen(map[0]);
	i = 0;
	if (filas == 0 || map == NULL)
		return (0);
	while (i < ancho)
	{
		if (map[0][i] != '1' || map[filas - 1][i] != '1')
			return (0);
		i ++;
	}
	i = 1;
	while (i < filas)
	{
		if (map[i][0] != '1' || map[i][ancho - 1] != '1')
			return (0);
		i ++;
	}
	return (1);
}
