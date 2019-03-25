/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 14:58:03 by squiquem          #+#    #+#             */
/*   Updated: 2019/03/25 19:35:24 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int				close_enough(t_dxy a, t_dxy b, double d)
{
	if (sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)) < d)
		return (1);
	return (0);
}

static t_dxy	door_gate(t_env *e)
{
	int		i;
	int		j;
	t_dxy	ret;

	j = (int)e->door.y;
	i = (int)e->door.x;
	if (!j || j == e->nbline - 1)
		ret = init_dxy(i, (j > 0 ? j - 1 : j + 1));
	else if (!i || i == e->linelen - 1)
		ret = init_dxy((i > 0 ? i - 1 : i + 1), j);
	else
		ret = new_door(e->worldmap, i, j);
	return (ret);
}

void			win(t_env *e)
{
	t_dxy	a;

//	a = init_dxy(e->door.x, e->door.y);
	a = door_gate(e);
	if (e->scrg.end_status != VICTORY && e->scrg.end_status != ULOSE)
		if (e->scrg.score == ENEMIES && close_enough(e->pos, a, 0.7))
		{
			e->scrg.end_status = VICTORY;
			e->scrg.endtime = (int)(e->time - e->start_time);
		}
}

void			lose(t_env *e, t_sprite s)
{
	t_dxy	a;

	a = init_dxy(s.x, s.y);
	if (e->scrg.end_status != VICTORY && e->scrg.end_status != ULOSE)
		if ((close_enough(a, e->pos, 0.5) && s.tex == 5 && !s.hidden)
				|| (!e->scrg.ammo_available && !e->bullet_start && !e->scrg.ammo
					&& e->scrg.score != ENEMIES))
		{
			e->scrg.end_status = ULOSE;
			e->scrg.endtime = (int)(e->time - e->start_time);
		}
}

void			end_screen(t_env *e)
{
	int h;
	int w;

	if (e->scrg.end_status == VICTORY)
	{
		if (!(e->img = mlx_xpm_file_to_image(e->mlx, "pics/victory.xpm",
						&w, &h)))
			print_error("Error mlx");
		mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
		print_endtime(e);
	}
	if (e->scrg.end_status == ULOSE)
	{
		if (!(e->img = mlx_xpm_file_to_image(e->mlx, "pics/pikachuko2.xpm", &w,
						&h)))
			print_error("Error mlx");
		mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
		print_endtime(e);
	}
}
