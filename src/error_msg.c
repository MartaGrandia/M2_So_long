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

int	error_texture(int error_code)
{
	if (error_code == 1)
		ft_printf("Error: No se puedo cargar un archivo wall.png\n");
	else if (error_code == 2)
		ft_printf("Error: No se puedo cargar un archivo floor.png\n");
	else if (error_code == 3)
		ft_printf("Error: No se puedo cargar un archivo collectible.png\n");
	else if (error_code == 4)
		ft_printf("Error: No se puedo cargar un archivo exit.png\n");
	else if (error_code == 5)
		ft_printf("Error: No se puedo cargar un archivo player.png\n");
	return (0);
}

int	print_map_error(int error_code)
{
	if (error_code == 1)
		ft_printf("Los elementos no estan bien \n");
	else if (error_code == 2)
		ft_printf("No llega a todos los colecionables\n");
	else if (error_code == 3)
		ft_printf("No es rectangular\n");
	else if (error_code == 4)
		ft_printf("NO tiene paret en todo el borde\n");
	return (0);
}
