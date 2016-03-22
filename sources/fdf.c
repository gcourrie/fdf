/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcourrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 17:00:24 by gcourrie          #+#    #+#             */
/*   Updated: 2016/03/22 17:19:38 by gcourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			fdf(int	**table, t_size size)
{
	void	*mlx_ptr;
	void	*win;

	(void)table;
	(void)size;
	mlx_ptr = mlx_init();
	win = mlx_new_window(mlx_ptr, 500, 500, "fdf");
	mlx_loop(mlx_ptr);
	return (0);
}
