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

typedef struct s_data
{
    mlx_t *mlx_ptr;
} t_data;

void on_destroy(mlx_t *mlx)
{
    mlx_terminate(mlx);
    exit(0);
}

void on_keypress(mlx_key_data_t keydata, void *param)
{
    mlx_t *mlx = (mlx_t *)param;  // Aquí casteamos correctamente el parámetro

    if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
    {
        ft_printf("Pressed key: %d\n", keydata.key);
        if (keydata.key == MLX_KEY_ESCAPE)
            on_destroy(mlx);
    }
}

int main(void)
{
    t_data data;

    data.mlx_ptr = mlx_init(600, 400, "hi :)", true);
    if (!data.mlx_ptr)
        return 1;

    // Pasamos data.mlx_ptr como parámetro a la función on_keypress
    mlx_key_hook(data.mlx_ptr, on_keypress, data.mlx_ptr);

    mlx_loop(data.mlx_ptr);

    mlx_terminate(data.mlx_ptr);

    return 0;
}

/*int	main(void)
{
	void	*mlx_ptr;

	mlx_ptr = mlx_init(256, 256, "MLX42", true);
	if (!mlx_ptr)
		return (1);
	mlx_loop(mlx_ptr);//mantiene la ventana abierta
	mlx_terminate(mlx_ptr);//cierra y libera todo a l salir
	//free(mlx_ptr);
	return (0);
}
*/

