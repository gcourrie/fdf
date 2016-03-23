/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcourrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 17:00:24 by gcourrie          #+#    #+#             */
/*   Updated: 2016/03/23 21:02:12 by gcourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "../minilibx_macos/mlx.h"
int			fdf(t_data e)
{
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, 500, 500, "fdf");
	mlx_expose_hook(e.win, expose_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}

static int	expose_hook(t_data *e)
{
	draw_fdf(e);
	return (0);
}

int			draw_fdf(t_data *e)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < e.y)
	{
		while (x < e.x)
		{
			print_lgn(x, y, e);
			x++;
		}
		y++;
	}
}

int			print_lgn(int x, int y, t_data *e)
{
	if (x == 0 && y == 1)
		pixel_put();
	else if (y == 1)
		hz_ligne_put(x, y, e);
	else if (x == 1)
		vr_ligne_put(x, y, e);
	else
	{
		hz_ligne_put(x, y, e);
		vr_ligne_put(x, y, e);
	}
	return (0);
}

int			hz_ligne_put(int x, int y, t_data *e)
{
	while ()
}

int			vr_ligne_put(int x, int y, t_data *e)
{

}
