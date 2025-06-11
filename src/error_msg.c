/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrandia <mgrandia@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:02:10 by mgrandia          #+#    #+#             */
/*   Updated: 2025/06/07 13:00:29 by mgrandia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// Muestra un mensaje de error específico si falla la carga de una textura
int	error_texture(int error_code)
{
	if (error_code == 1)
		ft_printf("Error: Could not load wall.png file\n");
	else if (error_code == 2)
		ft_printf("Error: Could not load floor.png file\n");
	else if (error_code == 3)
		ft_printf("Error: Could not load collectible.png file\n");
	else if (error_code == 4)
		ft_printf("Error: Could not load exit.png file\n");
	else if (error_code == 5)
		ft_printf("Error: Could not load player.png file\n");
	return (0);
}

// Muestra un mensaje de error específico si el mapa no es válido
int	print_map_error(int error_code)
{
	if (error_code == 1)
		ft_printf("Error: Invalid map elements\n");
	else if (error_code == 2)
		ft_printf("Error: Not all collectibles are reachable\n");
	else if (error_code == 3)
		ft_printf("Error: Map is not rectangular\n");
	else if (error_code == 4)
		ft_printf("Error: Map is not surrounded by wall\n");
	return (0);
}
