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
/*
static char	*read_line(int fd)
{
	char	*line;
	char	*new_line;
	size_t	len;
	int	b_read;
	char	c;

	line = malloc(1);
	len = 0;
	if (!line)
		return (NULL);
	line[0] = '\0';
	b_read = read(fd, &c, 1);
	while (b_read > 0)
	{
		if (c == '\n')
			break ;
		new_line = ft_realloc(line, len, len + 2);
		if (!new_line)
			return (ft_free(line));
		line = new_line;
		line[len] = c;
		line[len + 1] = '\0';
		len ++;
		b_read = read(fd, &c, 1);
	}
	if (len == 0)
		return (ft_free(line));
	//if (b_read == 0)
	//	return (NULL);
	return (line);
}*/

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
			ft_printf("ea");
			free(line);
			return (mapa);
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
/*	line = read_line(fd);
	if (ft_strncmp(&line[0],"\n", 1))
	{
		ft_printf("Hay un salto de linea");
		return (ft_free(line));
	}
	while (line != NULL)
	{
		temp = ft_realloc(mapa, sizeof(char *) * line_count,
				sizeof(char *) * (line_count + 2));
		if (!temp)
			return (free_map(mapa, line_count, line, fd));
		mapa = temp;
		mapa[line_count] = line;
		line_count ++;
		line = read_line(fd);
	}
	if (mapa)
		mapa[line_count] = NULL;
	if (filas)
		*filas = line_count;*/
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
