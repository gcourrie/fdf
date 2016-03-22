/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcourrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 17:20:04 by gcourrie          #+#    #+#             */
/*   Updated: 2016/03/22 17:25:13 by gcourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <stdio.h>

static int		*ft_put_str_in_int_tab(t_list *lst, int *size)
{
	int			i;
	int			n;
	int			*ret;
	char		*str;
	int			index;

	i = 0;
	index = 0;
	str = (char *)(lst->content);
	if (!(ret = (int *)malloc(sizeof(int) * (lst->content_size))))
		return (NULL);
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		n = i;
		while (str[n] != ' ' && str[n])
			n++;
		ret[index++] = ft_atoi(ft_strndup(str, i, n));
		i = n;
		if ((int)(lst->content_size) > *size)
			*size = lst->content_size;
		while ((int)(lst->content_size) < *size)
			ret[lst->content_size++] = 0;
	}
	return (ret);
}

static int		**fd_put_in_int_big_table(t_list *lst, int y,
											int **table, int *size)
{
	int			i;

	i = 0;
	if (!(table = (int **)malloc(sizeof(int *) * y)))
		return (NULL);
	while (lst)
	{
		table[i] = ft_put_str_in_int_tab(lst, size);
		lst = lst->next;
		i++;
	}
	return (table);
}

static size_t	ft_count_grp_int(char *str)
{
	size_t		i;

	i = 0;
	while (*str != '\0')
	{
		while (*str == ' ')
			str++;
		if (*str != ' ' && *str)
			i++;
		while (*str != ' ' && *str)
			str++;
	}
	return (i);
}

static t_list	*ft_map_into_list(int fd, t_list *lst, int *y)
{
	char	*str;
	t_list	*begin;

	get_next_line(fd, &str);
	lst = ft_lstnew(str, ft_count_grp_int(str));
	begin = lst;
	while (get_next_line(fd, &str))
	{
		lst->next = ft_lstnew(str, ft_count_grp_int(str));
		free(str);
		lst = lst->next;
		*y += 1;
	}
	return (begin);
}

static void		ft_affichage(int **table, t_list *lst, t_size size)
{
	int			i;
	int			n;
	int			sizex;

	i = 0;
	n = 0;
	sizex = size.x;
	while (size.y-- > 0)
	{
		sizex = size.x;
		printf("size.y = %d\n", size.y);
		printf("size.x = %d\n", size.x);
		printf("table [%d] = ", i);
		n = 0;
		while (sizex-- > 0)
			printf("%d ", table[i][n++]);
		i++;
		lst = lst->next;
		printf("\n");
	}
}

int				main(int ac, char **av)
{
	t_list	*lst;
	int		fd;
	int		**table;
	t_size	size;

	if (ac == 2)
	{
		size.x = 0;
		size.y = 0;
		table = NULL;
		lst = NULL;
		if ((fd = open(av[1], O_RDONLY)) < 0)
			return (-1);
		lst = ft_map_into_list(fd, lst, &(size.y));
		table = fd_put_in_int_big_table(lst, size.y, table, &(size.x));
		ft_affichage(table, lst, size);
//		fdf(table, size);
	}
	return (0);
}
