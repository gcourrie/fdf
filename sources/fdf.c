/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcourrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 17:00:24 by gcourrie          #+#    #+#             */
/*   Updated: 2016/04/06 07:37:13 by gcourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <stdio.h>
#include <math.h>

static void	eye_init(t_data *e)
{
	e->mid_x = -2;
	e->mid_y = -2;
	e->mid_z = -30;
	e->a_x = 1;
	e->a_y = 1;
	e->a_z = 1;
	e->w_x = 800;
	e->w_y = 600;
}

static int		ft_camera(t_data *e, t_point *point, int x, int y)
{
	int		z;

	z = e->table[y][x];
	p_x = x - e->mid_x;
	p_y = y - e->mid_y;
	p_z = z - e->mid_z;
	point->x = cos(e->a_z) * p_x - sin(e->a_z) * p_y
				+ p_x + cos(e->a_y)  * p_x + sin(e->a_y) * p_z;
	point->y = cos(e->a_x) * p_y - cos(e->a_x) * p_y
				+ p_y + cos(e->a_z)  * p_y + sin(e->a_z) * p_y;
	point->z = cos(e->a_y) * p_z - cos(e->a_y) * p_z
				+ p_z + cos(e->a_x)  * p_z + sin(e->a_x) * p_z;
//	point->x = (int)((point->x * 6) / (6 + point->z) * e->w_x / 3.5 + e->w_x);
//	point->y = (int)((point->y * 6) / (6 + point->z) * e->w_y / 3.5 + e->w_y);
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
	b = nd->y - a * nd->x;
	if (a < 1 && a > -1)
	{
		x1 = rst->x;
		x2 = nd->x;
		if (rst->x <= nd->x)
			while (x1 <= x2)
			{
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

	ft_camera(e, &actu, x, y);
	if (x + 1 < e->x)
	{
		ft_camera(e, &right, x + 1, y);
		draw_line(e, &actu, &right);
	}
	if (y + 1 < e->y)
	{
		ft_camera(e, &left, x, y + 1);
		draw_line(e, &actu, &left);
	}
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
