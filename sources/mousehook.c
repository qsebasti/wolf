/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mousehook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsebasti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 15:53:52 by qsebasti          #+#    #+#             */
/*   Updated: 2019/03/29 20:40:53 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	calc_angle(t_env *e, double angle)
{
	double	olddir;
	double	oldplane;

	olddir = e->dir.x;
	oldplane = e->plane.x;
	e->dir.x = olddir * cos(angle) - e->dir.y * sin(angle);
	e->dir.y = olddir * sin(angle) + e->dir.y * cos(angle);
	e->plane.x = oldplane * cos(angle) - e->plane.y * sin(angle);
	e->plane.y = oldplane * sin(angle) + e->plane.y * cos(angle);
	e->mouse.x = 0;
}

int			mousehook(int x, int y, t_env *e)
{
	e->mouse.x = x;
	e->mouse.y = y;
	rotate(e);
	return (0);
}

void		rotate(t_env *e)
{
	double	tmp;

	tmp = e->mouse.x * (M_PI / 180);
	if (tmp > M_PI / 24)
		tmp = M_PI / 24;
	else if (tmp < -M_PI / 24)
		tmp = -M_PI / 24;
	if (e->mouse.x != 0)
		calc_angle(e, tmp);
}
