/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcourrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 17:00:24 by gcourrie          #+#    #+#             */
/*   Updated: 2016/04/01 01:33:00 by gcourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <stdio.h>

static void	eye_init(t_data *e)
{
	e->mid_x = 6;
	e->mid_y = -2;
	e->mid_z = -10;
	e->x_x = 1;
	e->x_y = 0;
	e->x_z = 0;
	e->y_x = 0;
	e->y_y = 1;
	e->y_z = 0;
	e->z_x = 0;
	e->z_y = 0;
	e->z_z = 1;
	e->w_x = 800;
	e->w_y = 600;
}

static int		ft_camera(t_data *e, t_point *point, int x, int y)
{
	int		z;

//	printf("x = %d, y = %d\n", x, y);
	z = e->table[y][x];
	point->x = x * e->x_x + x * e->y_x + x * e->z_x - e->mid_x;
	point->y = y * e->x_y + y * e->y_y + y * e->z_y - e->mid_y;
	point->z = z * e->x_z + z * e->y_z + z * e->z_z - e->mid_z;
	point->x = (int)((point->x * 6) / (6 + point->z) * e->w_x / 3.5 + e->w_x);
	point->y = (int)((point->y * 6) / (6 + point->z) * e->w_y / 3.5 + e->w_y);
	return (0);
}

static int		put_pixel(t_data *e, int pointx, int pointy)
{
	printf("printx = %d printy = %d\n", pointx, pointy);
	if (pointx <= (e->w_x * 2) && pointx >= 0
		&& pointy <= (e->w_y * 2) && pointy >= 0)
		mlx_pixel_put(e->mlx, e->win, pointx, pointy, 0x00FFFFFF);
	return (0);
}

static int		draw_line(t_data *e, t_point *rst, t_point *nd)
{
	double		a;
	double		b;
	double		x1;
	double		x2;

	a = (rst->y - nd->y) / (rst->x - nd->x);
	printf("a = %f          rst->x = %d          rst->y = %d          nd->x = %d          nd->y = %d\n", a, (int)rst->x, (int)rst->y, (int)nd->x, (int)nd->y);
	b = nd->y - a * nd->x;
	if (a < 1 && a > -1)
	{
		x1 = rst->x;
		x2 = nd->x;
		printf("A\n");
		if (rst->x <= nd->x)
			while (x1 <= x2)
			{
				printf("a = %f          x1 = %d          x2 = %d\n", a, (int)x1, (int)x2);
				put_pixel(e, x1, x1 * a + b);
				x1 += 1;
			}
		else if (rst->x > nd->x)
			while (x1 >= x2)
			{
				put_pixel(e, x2, x2 * a + b);
				x2 += 1;
			}
	}
	if (a > 1 || a < -1)
	{
		printf("B\n");
		x1 = rst->y;
		x2 = nd->y;
		if (rst->y <= nd->y)
			while (x1 <= x2)
			{
				put_pixel(e, (x1 - b) / a, x1);
				x1 += 1;
			}
		else if (rst->y > nd->y)
			while (x1 >= x2)
			{
				put_pixel(e, (x1 - b) / a, x1);
				x2 += 1;
			}
	}
/* 	put_pixel(e, rst->x, rst->y); */
/* 	put_pixel(e, nd->x, nd->y); */
	return (0);
}

static int		point_draw(t_data *e, int x, int y)
{
	t_point		actu;
	t_point		right;
	t_point		left;

//	printf("B\n");
	ft_camera(e, &actu, x, y);
	if (x + 1 < e->x)
		ft_camera(e, &right, x + 1, y);
	if (y + 1 < e->y)
		ft_camera(e, &left, x, y + 1);
//	printf("\nprintx = %d          printy = %d          pointz = %d          x = %d          y = %d          z = %d\n\n", (int)actu.x, (int)actu.y, (int)actu.z, x, y, e->table[y][x]);
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
	while (y < e->y)
	{
		while (x < e->x)
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
	e.win = mlx_new_window(e.mlx, e.w_x * 2, e.w_y * 2, "fdf");
	mlx_expose_hook(e.win, expose_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}
