/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcourrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 13:31:51 by gcourrie          #+#    #+#             */
/*   Updated: 2016/03/23 20:33:16 by gcourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static void	clear_list(t_data e, t_lst *lst)
{
	int		i;

	i = 0;
	while (i++ < e.y)
	{
		if (lst->str)
			free(lst->str);
		if (lst)
			free(lst);
		lst = lst->next;
	}
	lst = NULL;
}

static int	**put_in_int_tab(t_data e, t_lst *begin)
{
	int		n;
	int		i;
	t_lst	*lst;


	i = 0;
	lst = begin;
	while (i < e.y)
	{
		n = 0;
		if (!(e.table[i] = (int *)ft_memalloc(sizeof(int) * e.x)))
			return (NULL);
		while (lst->str[n])
		{
			e.table[i][n] = ft_atoi(lst->str[n]);
			n++;
		}
		lst = lst->next;
		i++;
	}
	clear_list(e, begin);
	return (e.table);
}

static void     ft_affichage(t_data e)
{
    int         i;
    int         n;

    i = 0;
    n = 0;
    while (i < e.y)
    {
        n = 0;
        while (n < e.x)
        {
            printf("%d ", e.table[i][n]);
            n++;
        }
        i++;
        printf("\n");

    }
}

static int		ft_count_str(char **str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static t_lst	*get_the_struct(int fd, int *x, int *y, t_lst *begin)
{
	t_lst		*lst;
	t_lst		*pl;
	char		*tmp;

	while (get_next_line(fd, &tmp) > 0)
	{
		if (!(lst = (t_lst *)malloc(sizeof(t_lst))))
			return (0);
		if ((*y)++ == 0 && (begin = lst))
			pl = lst;
		if (*y != 1 && (pl->next = lst))
			pl = pl->next;
		lst->str = ft_strsplit(tmp, ' ');
		if (ft_count_str(lst->str) > *x)
			*x = ft_count_str(lst->str);
	}
	return (begin);
}

int				main(int ac, char **av)
{
	t_lst	*begin;
	t_data	e;
	int		fd;


	e.table = NULL;
	begin = NULL;
	e.x = 0;
	e.y = 0;
	if (ac == 2)
	{
		if ((fd = open(av[1], O_RDONLY)) < 0)
			return (0);
		begin = get_the_struct(fd, &(e.x), &(e.y), begin);
		if (!(e.table = (int **)malloc(sizeof(int *) * e.y)))
			return (0);
		e.table = put_in_int_tab(e, begin);
		ft_affichage(e);
		fdf(e);
	}
	return (0);
}
