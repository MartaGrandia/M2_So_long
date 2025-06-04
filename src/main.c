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
#include <fcntl.h>

void	*ft_free(void *ptr)
{
	free(ptr);
	return (NULL);
}

static char	**free_map(char **mapa, int line_count, char *line, int fd)
{
	int	i;

	i = 0;
	while (i < line_count)
	{
		free (mapa[i]);
		i ++;
	}
	free (mapa);
	free (line);
	close (fd);
	return (NULL);
}

char	*read_line(int fd)
{
	char	*line;
	char	*new_line;
	size_t	len;
	char	c;

	line = malloc(1);
	len = 0;
	if (!line)
		return (NULL);
	line[0] = '\0';
	while (read(fd, &c, 1) > 0)
	{
		if (c == '\n')
			break ;
		new_line = ft_realloc(line, len + 2);
		if (!new_line)
			return (ft_free(line));
		line = new_line;
		line[len] = c;
		line[len + 1] = '\0';
		len ++;
	}
	if (len == 0)
		return (ft_free(line));
	return (line);
}

char	**read_mapa(const char *ruta, int *filas)
{
	int		fd;
	char	**mapa;
	char	*line;
	int		line_count;
	char	**temp;

	fd = open(ruta, O_RDONLY);
	mapa = NULL;
	line_count = 0;
	if (fd < 0)
	{
		perror("Error al abrir el mapa");
		return (NULL);
	}
	line = read_line(fd);
	while (line != NULL)
	{
		temp = ft_realloc(mapa, sizeof(char *) * (line_count + 1));
		if (!temp)
			return (free_map(mapa, line_count, line, fd));
		mapa = temp;
		mapa[line_count] = line;
		line_count ++;
		line = read_line(fd);
	}
	close(fd);
	if (filas)
		*filas = line_count;
	return (mapa);
}

int32_t	main(void)
{
	int		filas;
	char	**mapa;
	int		i;

	filas = 0;
	mapa = read_mapa("./maps/map1.ber", &filas);
	i = 0;
	if (!mapa)
		return (1);
	while (i < filas)
	{
		ft_printf("%s\n", mapa[i]);
		free(mapa[i]);
		i ++;
	}
	free(mapa);
}
