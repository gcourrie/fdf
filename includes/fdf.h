/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcourrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 11:47:27 by gcourrie          #+#    #+#             */
/*   Updated: 2016/03/23 19:34:37 by gcourrie         ###   ########.fr       */
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
}					t_data;

typedef struct		s_lst
{
	char			**str;
	struct s_lst	*next;
}					t_lst;

int					fdf(t_data e);

#endif
