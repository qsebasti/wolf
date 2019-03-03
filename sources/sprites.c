/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 15:02:34 by squiquem          #+#    #+#             */
/*   Updated: 2018/07/19 17:02:24 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	draw_one_sprite(t_env *e, t_sprite spr)
{
	t_dxy		sprite;
	t_dxy		trfm;
	t_ixy		spriteonscreen;
	t_sgmt		drawy;

	sprite = (t_dxy){spr.x - e->pos.x, spr.y - e->pos.y};
	trfm = calc_trfm(e, spr);
	spriteonscreen = calc_spriteonscreen(spr, trfm);
	e->spritescreenx = (int)((IMG_W / 2) * (1 + trfm.x / trfm.y));
	drawy.start = (IMG_H - spriteonscreen.y) / 2 + (int)(spr.offset / trfm.y);
	(drawy.start < 0) ? drawy.start = 0 : drawy.start;
	drawy.end = (spriteonscreen.y + IMG_H) / 2 + (int)(spr.offset / trfm.y);
	(drawy.end >= IMG_H) ? drawy.end = IMG_H - 1 : drawy.end;
	stripe_loop(drawy, spriteonscreen, e, spr);
}

void	draw_sprites(t_env *e)
{
	int			i;
	t_sprite	spr;

	sprite_sort(e);
	i = -1;
	while (++i < NUMSPRITES)
	{
		spr = e->sprite[e->spritesorder[i]];
		lose(e, spr);
		pick_up(&e->sprite[e->spritesorder[i]], e);
		draw_one_sprite(e, spr);
		if (!spr.hidden && spr.tex == 5)
			choose_direction(e, &e->sprite[e->spritesorder[i]]);
	}
}

/*
**	Tri des sprites suivant la distance
*/

void	sprite_sort(t_env *e)
{
	int	i;

	i = -1;
	while (++i < NUMSPRITES)
	{
		e->spritesorder[i] = i;
		e->spritesdistance[i] = (e->pos.x - e->sprite[i].x) *
			(e->pos.x - e->sprite[i].x)
			+ (e->pos.y - e->sprite[i].y) * (e->pos.y - e->sprite[i].y);
	}
	ft_combsort(e->spritesorder, e->spritesdistance, NUMSPRITES);
}

void	pick_up(t_sprite *spri, t_env *e)
{
	t_dxy	p;

	p = (t_dxy){spri->x, spri->y};
	if (close_enough(e->pos, p, 0.5) && !spri->hidden && spri->tex == 3)
	{
		spri->hidden = 1;
		e->scrg.ammo++;
		e->scrg.ammo_available--;
	}
}

void	ft_combsort(int *order, double *dist, int amount)
{
	int	gap;
	int swapped;
	int	i;
	int	j;

	gap = amount;
	swapped = 0;
	while (gap > 1 || swapped)
	{
		gap = (gap * 10) / 13;
		(gap == 9 || gap == 10) ? gap = 11 : gap;
		gap < 1 ? gap = 1 : gap;
		swapped = 0;
		i = -1;
		while (++i < amount - gap)
		{
			j = i + gap;
			if (dist[i] < dist[j])
			{
				ft_dswap(dist + i, dist + j);
				ft_swap(order + i, order + j);
				swapped = 1;
			}
		}
	}
}
