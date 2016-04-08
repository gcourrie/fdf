/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcourrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/08 03:13:09 by gcourrie          #+#    #+#             */
/*   Updated: 2016/04/08 04:53:04 by gcourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int		key_hook(int keycode, t_data *e)
{
	(void)e;
	printf("key :%d\n", keycode);
	if (keycode == 126)
		e->mid_x += 1;
	if (keycode == 125)
		e->mid_x -= 1;
	if (keycode == 53)
	{
		mlx_destroy_window(e->mlx, e->win);
		exit(0);
	}
	return (0);
}
