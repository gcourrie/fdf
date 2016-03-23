/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcourrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 13:31:51 by gcourrie          #+#    #+#             */
/*   Updated: 2016/03/23 16:18:03 by gcourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static void	clear_list(t_lst **lst)
{
	while (lst)
	{
		free((*lst)->str);
		free(*lst);
		*lst = (*lst)->next;
	}
	*lst = NULL;
}

static int	**put_in_int_tab(int **table, t_size size, t_lst *lst, t_lst *begin)
{
	int		n;
	int		i;


	i = 0;
	n = 0;
	if (!(table = (int **)malloc(sizeof(int *) * size.y)))
		return (0);
	lst = begin;
	while (lst)
	{
		if (!(table[i] = (int *)ft_memalloc(sizeof(int) * size.x)))
			return (0);
		while (lst->str[n])
		{
			table[i][n] = ft_atoi(lst->str[n]);
			n++;
		}
		lst = lst->next;
		i++;
	}
	clear_list(&begin);
	return (table);
}

static void     ft_affichage(int **table, int x, int y)
{
    int         i;
    int         n;

    i = 0;
    n = 0;
    while (i < y)
    {
        n = 0;
        while (n < x)
        {
            printf("%d ", table[i][n]);
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
	while (str++)
		i++;
	return (i);
}

int				main(int ac, char **av)
{
	int		**table;
	t_lst	*begin;
	t_lst	*lst;
	t_size	size;
	int		fd;
	char	*tmp;

	lst = NULL;
	table = NULL;
	printf("A");
	if (ac == 2)
	{
		printf("A");
		if ((fd = open(av[1], O_RDONLY)) < 0)
			return (0);
		while (get_next_line(fd, &tmp) > 0)
		{
			if (!(lst = (t_lst *)malloc(sizeof(t_lst))))
				return (0);
			if (ac++ == 2)
				begin = lst;
			lst->str = ft_strsplit(tmp, ' ');
			if (ft_count_str(lst->str) > size.y)
				size.y = ft_count_str(lst->str);
			lst = lst->next;
		}
		table = put_in_int_tab(table, size, lst, begin);
		ft_affichage(table, size.x, size.y);
	}
	return (0);
}
