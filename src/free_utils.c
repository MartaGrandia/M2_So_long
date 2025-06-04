/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrandia <mgrandia@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:02:10 by mgrandia          #+#    #+#             */
/*   Updated: 2025/05/31 17:17:15 by mgrandia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	*ft_free(void *ptr)
{
	free(ptr);
	return (NULL);
}

char	**free_map(char **mapa, int line_count, char *line, int fd)
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
