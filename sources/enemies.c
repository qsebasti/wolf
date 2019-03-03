/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 18:34:12 by squiquem          #+#    #+#             */
/*   Updated: 2018/06/29 15:54:04 by squiquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	move_enemy(t_env *e, t_sprite *s, int r)
{
	double	t;

	t = (e->time - e->oldtime) / 2000;
	if (r == 0 && !(e->worldmap[(int)(s->x + 1.0)][(int)s->y]))
		s->x += t;
	else if (r == 1 && !(e->worldmap[(int)s->x][(int)(s->y + 1.0)]))
		s->y += t;
	else if (r == 2 && !(e->worldmap[(int)(s->x - 1.0)][(int)s->y]))
		s->x -= t;
	else if (r == 3 && !(e->worldmap[(int)s->x][(int)(s->y - 1.0)]))
		s->y -= t;
}

void	choose_direction(t_env *e, t_sprite *s)
{
	if (e->time - s->move_time <= 1000)
		move_enemy(e, s, s->random);
	if (e->time - s->move_time > 1000)
	{
		s->move_time = e->time;
		s->random = rand() % 4;
	}
}
