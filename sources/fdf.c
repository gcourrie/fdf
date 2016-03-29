/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcourrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 17:00:24 by gcourrie          #+#    #+#             */
/*   Updated: 2016/03/29 18:46:25 by gcourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "../minilibx_macos/mlx.h"
#include <stdio.h>

static void	eye_init(t_data *e)
{
	e->mid_x = 0;
	e->mid_y = 0;
	e->mid_z = 0;
	e->x_x = 1 + e->mid_x;
	e->x_y = 0 + e->mid_y;
	e->x_z = 0 + e->mid_z;
	e->y_x = 0 + e->mid_x;
	e->y_y = 1 + e->mid_y;
	e->y_z = 0 + e->mid_z;
	e->z_x = 0 + e->mid_x;
	e->z_y = 0 + e->mid_y;
	e->z_z = 1 + e->mid_z;
}

static int		ft_camera(t_data *e, t_point *point, int x, int y)
{
	int		z;

	printf("x = %d, y = %d\n", x, y);
	printf("table[%d][%d] = %d\n", y, x, e->table[y][x]);
	z = e->table[y][x];
	printf("C\n");
	point->x = x * e->x_x + x * e->y_x + x * e->z_x;
	printf("C\n");
	point->y = y * e->x_y + y * e->y_y + y * e->z_y;
	printf("C\n");
	point->z = z * e->x_z + z * e->y_z + z * e->z_z;
	printf("C\n");
	point->x = (point->x * 6) / (6 + point->z);
	printf("C\n");
	point->y = (point->y * 6) / (6 + point->z);
	printf("C\n");
	return (0);
}

static int		draw_line(t_data *e, t_point *rst, t_point *nd)
{
	double		pointx;
	double		pointy;

	pointx = rst->x;
	pointy = rst->y;
	(void)nd;
	if ((pointx <= 3.5 && pointx >= -3.5) && (pointy <= 3.5 && pointy >= -3.5))
		mlx_pixel_put(e->mlx, e->win, ((pointx * 320 / 3.5) + 320), ((pointy * 240 / 3.5) + 240), 0x00FFFFFF);
	return (0);
}

static int		point_draw(t_data *e, int x, int y)
{
	t_point		actu;
	t_point		right;
	t_point		left;

	printf("B\n");
	ft_camera(e, &actu, x, y);
	printf("C\n");
	if (x + 1 <= e->x)
		ft_camera(e, &right, x + 1, y);
	if (y + 1 <= e->y)
		ft_camera(e, &left, x, y + 1);
	printf("printx = %f printy = %f pointz = %f x = %d y = %d z = %d\n", actu.x, actu.y, actu.z, x, y, e->table[y][x]);
	draw_line(e, &actu, &right);
	draw_line(e, &actu, &left);
	return (0);
}

static int	draw_fdf(t_data *e)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y <= e->y)
	{
		while (x <= e->x)
		{
			point_draw(e, x, y);
			x += 1;
		}
		x = 0;
		y += 1;
	}
	return (0);
}

static int	expose_hook(t_data *e)
{
	draw_fdf(e);
	return (0);
}

int			fdf(t_data e)
{
	eye_init(&e);
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, 640, 480, "fdf");
	mlx_expose_hook(e.win, expose_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}
