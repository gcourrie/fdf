/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcourrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 17:00:24 by gcourrie          #+#    #+#             */
/*   Updated: 2016/03/28 18:46:24 by gcourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "../minilibx_macos/mlx.h"
int			fdf(t_data e)
{
	eye_init(&e);
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, 640, 480, "fdf");
	mlx_expose_hook(e.win, expose_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}

static int	expose_hook(t_data *e)
{
	draw_fdf(e);
	return (0);
}

static int	draw_fdf(t_data *e)
{
	int		x;
	int		y;

	x = e.x;
	y = e.y;
	while (y > 0)
	{
		while (x > 0)
		{
			point_draw(e, x, y);
			x--;
		}
		x = e.x;
		y--;
	}
}

int			point_draw(e, x, y)
{
	int		xres;
	int		yres;

	pointx = x * e.x_x + x * e.y_x + x * e.z_x;
	pointy = y * e.x_y + y * e.y_y + y * e.z_y;
	pointz = table[y][x] * e.x_z + table[y][x] * e.y_z + table[y][x] * e.z_z;
	pointx = (6 * (pointx - e.eye_x)) / (6 + pointz) + e.eye_x;
	pointy = (6 * (pointy - e.eye_y)) / (6 + pointz) + e.eye_y;

	mlx_pixel_put(e.mlx, e.win, pointx, pointy);
}

static void	eye_init(t_data *e)
{
	e.mid_x = 0;
	e.mid_y = 0;
	e.mid_z = 0;
	e.x_x = 1 + e.mid_x;
	e.x_y = 0 + e.mid_y;
	e.x_z = 0 + e.mid_z;
	e.y_x = 0 + e.mid_x;
	e.y_y = 1 + e.mid_y;
	e.y_z = 0 + e.mid_z;
	e.z_x = 0 + e.mid_x;
	e.z_y = 0 + e.mid_y;
	e.z_z = 1 + e.mid_z;
}
