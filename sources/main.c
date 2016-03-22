/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcourrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 17:20:04 by gcourrie          #+#    #+#             */
/*   Updated: 2016/03/22 14:13:45 by gcourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx_macos/mlx.h"
#include "../includes/fdf.h"

static int		*ft_put_str_in_int_tab(int *tmp, t_list *lst)
{
	int			i;
	int			n;
	int			*ret;

	i = 0;
	if (!(tmp = (int *)malloc(sizeof(int) * (lst->content_size))))
		return (NULL);
	ret = tmp;
	while (lst->content[i])
	{
		while (lst->content[i] == ' ')
			i++;
		n = i;
		while (lst->content[n] != ' ' && lst->content[n])
			n++;
		*tmp++ = ft_atoi(ft_strndup(lst->content, i, n));
		i = n;
	}
	return (ret);
}

static int		**fd_put_in_int_big_table(t_list *lst, int ac, int **table)
{
	int			**tmp;

	if (!(table = (int **)malloc(sizeof(int *) * ac)))
		return (NULL);
	tmp = table;
	while (lst)
	{
		*tmp = ft_put_str_in_int_tab(*tmp, lst);
		lst = lst->next;
		tmp++;
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

static t_list	*ft_map_into_list(int fd, t_list *lst, int *ac)
{
	char	*str;
	t_list	*begin;

	get_next_line(fd, &str);
	lst = ft_lstnew(str, ft_strlen(str));
	begin = lst;
	while (get_next_line(fd, &str))
	{
		lst->next = ft_lstnew(str, ft_count_grp_int(str));
		free(str);
		lst = lst->next;
		ac++;
	}
	return (begin);
}

int		main(int ac, char **av)
{
	void	*mlx_ptr;
	t_list	*lst;
	int		fd;
	int		**table;

	if (ac-- == 2)
	{
		if ((fd = open(av[1], O_RDONLY)) < 0)
			return (-1);
		lst = ft_map_into_list(fd, lst, &ac);
		table = fd_put_in_int_big_table(lst, ac, table);
		mlx_ptr = mlx_init();
		mlx_new_window(mlx_ptr, 500, 500, "fdf");
		mlx_loop(mlx_ptr);
	}
	return (0);
}
