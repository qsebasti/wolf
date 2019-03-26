/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bullet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 15:02:34 by squiquem          #+#    #+#             */
/*   Updated: 2019/03/26 17:24:23 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			key_hook_shoot(int button, int x, int y, t_env *e)
{
	if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
	{
		if (button == 1 && !e->bullet_start && e->scrg.ammo != 0)
		{
			e->bullet = (t_bullet){{e->pos.x, e->pos.y, 4, 50, 5, 0, 0, 0},
				e->dir, e->pos};
			//e->bullet.sprite = init_sprite(e->pos.x, e->pos.y, 4, e);
			//e->bullet.dir = e->dir;
			//e->bullet.pos = e->pos;
			e->shoot_time = get_time();
			e->bullet_start = 1;
			e->scrg.ammo--;
		}
	}
	return (0);
}

static int	check_hit(t_env *e)
{
	int			i;
	t_sprite	s;
	t_dxy		a;
	t_dxy		b;

	i = -1;
	while (++i < NUMSPRITES)
	{
		s = e->sprite[e->spritesorder[i]];
		a = init_dxy(e->bullet.sprite.x, e->bullet.sprite.y);
		b = init_dxy(s.x, s.y);
		if (s.tex == 5 && close_enough(a, b, 0.5) && !s.hidden)
		{
			e->sprite[e->spritesorder[i]].hidden = 1;
			e->scrg.score++;
			e->scrg.livingenemies--;
			return (1);
		}
	}
	return (0);
}

static void	move_bullet(t_env *e)
{
	e->bullet.sprite.x += e->bullet.dir.x * (e->time - e->shoot_time) / 1000;
	e->bullet.sprite.y += e->bullet.dir.y * (e->time - e->shoot_time) / 1000;
}

void		draw_bullet(t_env *e)
{
	t_dxy		sprite;
	t_dxy		trfm;
	t_ixy		spriteonscreen;
	t_sgmt		drawy;
	t_sprite	spr;

	spr = e->bullet.sprite;
	sprite = init_dxy(spr.x - e->pos.x, spr.y - e->pos.y);
	trfm = calc_trfm(e, spr);
	spriteonscreen = calc_spriteonscreen(spr, trfm);
	e->spritescreenx = (int)((IMG_W / 2) * (1 + trfm.x / trfm.y));
	drawy.start = (IMG_H - spriteonscreen.y) / 2 + (int)(spr.offset / trfm.y);
	(drawy.start < 0) ? drawy.start = 0 : drawy.start;
	drawy.end = (spriteonscreen.y + IMG_H) / 2 + (int)(spr.offset / trfm.y);
	(drawy.end >= IMG_H) ? drawy.end = IMG_H - 1 : drawy.end;
	stripe_loop_bullet(drawy, spriteonscreen, e, spr);
	if (check_hit(e))
		e->bullet_start = 0;
	if (sqrt(pow(e->bullet.sprite.x, 2) + pow(e->bullet.sprite.y, 2)) > 24)
		e->bullet_start = 0;
	move_bullet(e);
}
