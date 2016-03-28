/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcourrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 11:47:27 by gcourrie          #+#    #+#             */
/*   Updated: 2016/03/28 17:49:20 by gcourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../includes/libft.h"
# include <fcntl.h>
#include "../minilibx_macos/mlx.h"

typedef struct		s_data
{
	int				x;
	int				y;
	void			*mlx;
	void			*win;
	int				**table;
	int				eye_x;
	int				eye_y;
	int				eye_z;
	int				x_x;
	int				x_y;
	int				x_z;
	int				y_x;
	int				y_y;
	int				y_z;
	int				z_x;
	int				z_y;
	int				z_z;

}					t_data;


typedef struct		s_lst
{
	char			**str;
	struct s_lst	*next;
}					t_lst;

int					fdf(t_data e);

#endif
