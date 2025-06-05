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
