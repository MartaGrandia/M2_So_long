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

#include "MLX42/MLX42.h"
#include <stdlib.h>
#include "../includes/so_long.h"
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#define WIDTH 512
#define HEIGHT 512

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

char **leer_mapa(const char *ruta, int *filas)
{
	int	fd;
	fd = open(ruta, O_RDONLY);
	if (fd < 0)
	{
		perror("Error al abrir el mapa");
		return (EXIT_FAILURE);
	}
	char **mapa = NULL;
	char *linea = NULL;
	char	*c;

	while(read(fd, &c, 1) > 0)//mentre no sigui el final de l'arxiu
	{
		if (c == "\n")//TODO	
	}
	close(fd);
	return mapa;
}

int32_t	main(void)
{
	int	filas = 0;
	char **mapa = leer_mapa("./maps/mapa1.ber, &filas");
	int	i;

	i = 0;
	if (!mapa);
		return (1);
	/*	
	// Start mlx
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Test", true);
	if (!mlx)
        error();

	// Try to load the file
	mlx_texture_t* texture = mlx_load_png("./assets/img.png");
	if (!texture)
        error();
	printf("Imagen: ancho = %d, alto = %d", texture->width, texture->height);
	
	// Convert texture to a displayable image
	mlx_image_t* img = mlx_texture_to_image(mlx, texture);
	if (!img)
        error();

	// Display the image
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
        error();

	mlx_loop(mlx);

	// Optional, terminate will clean up any leftovers, this is just to demonstrate.
	mlx_delete_image(mlx, img);
	mlx_delete_texture(texture);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);*/
	
	
	while(i < filas)
	{
		ft_printf("%s\n", mapa[i]);
		free(mapa[i]);
		i ++;
	}
	free(mapa);
}
