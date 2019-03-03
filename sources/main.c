/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 17:07:15 by squiquem          #+#    #+#             */
/*   Updated: 2018/09/24 20:45:03 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		print_error(char *cause)
{
	ft_putendl_fd(cause, 2);
	exit(1);
}

int			quit(void)
{
	exit(1);
	return (0);
}

int			main(int ac, char **av)
{
	t_env	*e;

	if (!(e = (t_env*)malloc(sizeof(t_env))))
		print_error("Error malloc");
	if (!(e->mlx = mlx_init()))
		print_error("Error mlx init");
	if (ac != 2)
		print_error("Only 1 argument");
	if (ft_read(av[1], e) == -1)
		print_error("Non valid map");
	init(e);
	e->win = mlx_new_window(e->mlx, WIN_W, WIN_H, "wolf3d");
	mlx_centertop_window(e->win);
	mlx_loop_hook(e->mlx, reload, e);
	mlx_hook(e->win, KPRESS, KPRESSMASK, keypress, e);
	mlx_hook(e->win, KRELEASE, KRELEASEMASK, keyrelease, e);
	mlx_hook(e->win, DESTROY, SNOTIFYMASK, quit, e);
	mlx_hook(e->win, MOTION_NOTIFY, PTR_MOTION_MASK, mousehook, e);
	mlx_mouse_hook(e->win, key_hook_shoot, e);
	mlx_loop(e->mlx);
	return (1);
}
