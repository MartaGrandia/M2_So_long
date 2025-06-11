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

// Procesa una línea leída del archivo para el mapa:
// - Elimina el carácter '\n' si está presente al final.
// - Verifica que la línea no esté vacía (no sea una línea en blanco).
//   Si es línea en blanco, imprime error, libera memoria y retorna NULL.
// Retorna la línea procesada o NULL en caso de error.
static char	*process_line(char *line)
{
	char	*ptr;

	ptr = ft_strchr(line, '\n');
	if (ptr)
		*ptr = '\0';
	if (ft_strlen(line) == 0)
	{
		ft_printf("Error: Blank line detected in map\n");
		free(line);
		return (NULL);
	}
	return (line);
}

// Añade una línea al mapa dinámicamente:
// - Realoca el array de punteros para añadir una nueva línea más un NULL final.
// - Duplica la línea recibida y la añade en la posición 'line_count'.
// Retorna el nuevo mapa (puntero) actualizado o NULL si falla la realocación.
static char	**add_line_to_map(char **mapa, char *line, int line_count)
{
	char	**temp;

	temp = ft_realloc(mapa, sizeof(char *) * line_count,
			sizeof(char *) * (line_count + 2));
	if (!temp)
		return (NULL);
	mapa = temp;
	mapa[line_count] = ft_strdup(line);
	return (mapa);
}

// Lee todas las líneas del archivo asociado al descriptor 'fd' y crea el mapa:
// - Lee línea a línea usando get_next_line.
// - Procesa cada línea con process_line para validar y limpiar.
// - Agrega cada línea procesada al mapa dinámico con add_line_to_map.
// - En caso de error libera toda la memoria y cierra el descriptor.
// - Al finalizar, almacena en 'filas' la cantidad de líneas leídas.
// Retorna el mapa como un array de cadenas terminado en NULL o NULL en caso de error.
static char	**read_mapa_from_fd(int fd, int *filas)
{
	char	**mapa;
	char	*line;
	int		line_count;

	mapa = NULL;
	line_count = 0;
	line = get_next_line(fd);
	if (!line)
		return (NULL);
	while (line != NULL)
	{
		line = process_line(line);
		if (!line)
			return (NULL);
		mapa = add_line_to_map(mapa, line, line_count);
		if (!mapa)
			return (free_map(mapa, line_count, line, fd));
		line_count ++;
		free(line);
		line = get_next_line(fd);
	}
	*filas = line_count;
	return (mapa);
}

char	**read_map(const char *ruta, int *filas)
{
	int		fd;
	char	**mapa;

	fd = open(ruta, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error: Could not open the map\n");
		return (NULL);
	}
	mapa = read_mapa_from_fd(fd, filas);
	close(fd);
	return (mapa);
}
