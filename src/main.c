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

int32_t	main(void)
{
	int		filas;
	char	**mapa;
	int		i;

	filas = 0;
	mapa = read_map("./maps/map1.ber", &filas);
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
