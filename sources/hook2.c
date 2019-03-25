/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 16:33:39 by squiquem          #+#    #+#             */
/*   Updated: 2019/03/25 19:36:14 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "keyboard.h"

int		keypress(int keycode, t_env *e)
{
	if (keycode == KEY_ENTER && !e->key[KEY_ENTER])
	{
		e->start_time = get_time();
		e->key[keycode] = 1;
	}
	else if (keycode == KEY_TAB)
		e->key[KEY_TAB] = (e->key[KEY_TAB] == 0 ? 1 : 0);
	else
		e->key[keycode] = 1;
	return (0);
}

int		keyrelease(int keycode, t_env *e)
{
	if (keycode == KEY_ENTER || keycode == KEY_TAB)
		return (0);
	e->key[keycode] = 0;
	return (0);
}

int		check_barrier(t_env *e, double x, double y)
{
	int			i;
	t_sprite	spr;
	t_dxy		pos;
	t_dxy		spr_pos;

	pos = init_dxy(x, y);
	i = -1;
	while (++i < NUMSPRITES)
	{
		spr = e->sprite[e->spritesorder[i]];
		spr_pos = init_dxy(spr.x, spr.y);
		if (spr.tex == 0 || spr.tex == 1)
		{
			if (close_enough(pos, spr_pos, 0.5))
				return (1);
		}
	}
	return (0);
}
