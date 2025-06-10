/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrandia <mgrandia@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:02:10 by mgrandia          #+#    #+#             */
/*   Updated: 2025/06/09 19:05:07 by mgrandia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static char	**read_mapa_from_fd(int fd, int *filas)
{
	char	**mapa;
	char	*line;
	int	line_count;
	char	**temp;
	char	*ptr;

	(void) filas;
	mapa = NULL;
	line_count = 0;
	line = get_next_line(fd);
	if (!line)
		return (NULL);
	while (line != NULL)
	{
		ptr = ft_strchr(line, '\n');
		if (ptr)
			*ptr = '\0';
		if (ft_strlen(line) == 0)
		{
			ft_printf("Error: El mapa tiene una linea en blanco");
			free(line);
			return (NULL);
		}
				
		temp = ft_realloc(mapa, sizeof(char *) * line_count,
				sizeof(char *) * (line_count + 2));
		if (!temp)
			return (free_map(mapa, line_count, line, fd));
		mapa = temp;
		mapa[line_count] = ft_strdup(line);
		line_count ++;
		free(line);
		line = get_next_line(fd);
	}
	return (mapa);
}

char	**read_map(const char *ruta, int *filas)
{
	int		fd;
	char	**mapa;

	fd = open(ruta, O_RDONLY);
	if (fd < 0)
	{
		perror("Error al abrir el mapa");
		return (NULL);
	}
	mapa = read_mapa_from_fd(fd, filas);
	close(fd);
	return (mapa);
}
