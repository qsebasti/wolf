/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsebasti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 18:43:48 by qsebasti          #+#    #+#             */
/*   Updated: 2019/03/30 12:02:13 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_sprite	init_sprite(int x, int y, int type, t_env *e)
{
	t_sprite	s;

	ft_bzero(&s, sizeof(s));
	s.x = x;
	s.y = y;
	s.tex = type;
	s.scale = 1;
	if (type == 3)
		s.offset = 384;
	else if (type == 5)
	{
		s.offset = -150;
		s.move_time = e->time;
	}
	else if (type == 4)
	{
		s.offset = 50;
		s.scale = 5;
	}
	return (s);
}

t_ixy		init_ixy(int x, int y)
{
	t_ixy	point;

	point.x = x;
	point.y = y;
	return (point);
}

t_dxy		init_dxy(double x, double y)
{
	t_dxy	point;

	point.x = x;
	point.y = y;
	return (point);
}

t_sgmt		init_sgmt(int start, int end)
{
	t_sgmt	s;

	s.start = start;
	s.end = end;
	return (s);
}
