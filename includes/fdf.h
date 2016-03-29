/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcourrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 11:47:27 by gcourrie          #+#    #+#             */
/*   Updated: 2016/03/29 17:58:00 by gcourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../includes/libft.h"
# include <fcntl.h>
#include "../minilibx_macos/mlx.h"
typedef struct		s_point
{
	double			x;
	double			y;
	double			z;
}					t_point;

typedef struct		s_data
{
	int				x;
	int				y;
	int				x2;
	int				y2;
	void			*mlx;
	void			*win;
	int				**table;
	double			mid_x;
	double			mid_y;
	double			mid_z;
	double			x_x;
	double			x_y;
	double			x_z;
	double			y_x;
	double			y_y;
	double			y_z;
	double			z_x;
	double			z_y;
	double			z_z;

}					t_data;


typedef struct		s_lst
{
	char			**str;
	struct s_lst	*next;
}					t_lst;

int					fdf(t_data e);

#endif
