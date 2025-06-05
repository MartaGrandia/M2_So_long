/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrandia <mgrandia@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:02:10 by mgrandia          #+#    #+#             */
/*   Updated: 2025/05/31 17:17:15 by mgrandia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	find_player(char **map, int *x, int *y)
{
	int	fil;
	int	col;

	fil = 0;
	while (map[fil])
	{
		col = 0;
		while (map[fil][col])
		{
			if (map[fil][col] == 'P')
			{
				*x = col;
				*y = fil;
				return ;
			}
			col ++;
		}
		fil++;
	}
}


