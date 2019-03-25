/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 15:02:34 by squiquem          #+#    #+#             */
/*   Updated: 2019/03/25 19:29:49 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_dxy	calc_trfm(t_env *e, t_sprite spr)
{
	t_dxy		trfm;
	double		invdet;
	t_dxy		sprite;

	sprite = init_dxy(spr.x - e->pos.x, spr.y - e->pos.y);
	invdet = 1.0 / (e->plane.x * e->dir.y - e->plane.y * e->dir.x);
	trfm.x = invdet * (e->dir.y * sprite.x - e->dir.x * sprite.y);
	trfm.y = invdet * (e->plane.x * sprite.y - e->plane.y * sprite.x);
	return (trfm);
}

t_ixy	calc_spriteonscreen(t_sprite spr, t_dxy trfm)
{
	t_ixy		spriteonscreen;

	spriteonscreen.y = abs((int)(IMG_H / trfm.y)) / spr.scale;
	spriteonscreen.x = abs((int)(IMG_H / trfm.y)) / spr.scale;
	return (spriteonscreen);
}

int		calc_sprite_texy(t_env *e, t_ixy spriteonscreen, t_sprite spr,
		t_ixy p)
{
	int		texy;
	t_dxy	trfm;

	trfm = calc_trfm(e, spr);
	texy = ((p.y - (int)(spr.offset / trfm.y)) * 256 - IMG_H * 128
			+ spriteonscreen.y * 128) * e->obj[spr.tex].size.y
			/ spriteonscreen.y / 256;
	return (texy);
}

void	stripe_loop(t_sgmt drawy, t_ixy spriteonscreen, t_env *e, t_sprite s)
{
	t_dxy	trfm;
	int		stp;
	t_ixy	p;
	t_ixy	tex;
	t_color	c;

	trfm = calc_trfm(e, s);
	stp = (e->spritescreenx - spriteonscreen.x / 2 > 0 ?
			-spriteonscreen.x / 2 + e->spritescreenx - 1 : -1);
	while (++stp < e->spritescreenx + spriteonscreen.x / 2 && stp < IMG_W)
	{
		tex.x = (int)(256 * (stp - (-spriteonscreen.x / 2 + e->spritescreenx))
				* e->obj[s.tex].size.x / spriteonscreen.x) / 256;
		if (trfm.y > 0 && stp > 0 && stp < IMG_W && trfm.y < e->zbuffer[stp])
		{
			p = init_ixy(stp, drawy.start - 1);
			while (++p.y < drawy.end)
			{
				tex.y = calc_sprite_texy(e, spriteonscreen, s, p);
				get_img_color(&e->obj[s.tex], tex, &c);
				if ((c.red != 0 || c.blue != 0 || c.green != 0) && !s.hidden)
					draw_point(e, p, &c);
			}
		}
	}
}

void	stripe_loop_bullet(t_sgmt drawy, t_ixy spriteonscreen, t_env *e,
		t_sprite s)
{
	t_dxy	trfm;
	int		stp;
	t_ixy	p;
	t_ixy	tex;
	t_color	c;

	trfm = calc_trfm(e, s);
	stp = (e->spritescreenx - spriteonscreen.x / 2 > 0 ?
			-spriteonscreen.x / 2 + e->spritescreenx - 1 : -1);
	while (++stp < e->spritescreenx + spriteonscreen.x / 2 && stp < IMG_W)
	{
		tex.x = (int)(256 * (stp - (-spriteonscreen.x / 2 + e->spritescreenx))
				* e->obj[s.tex].size.x / spriteonscreen.x) / 256;
		if (trfm.y > 0 && stp > 0 && stp < IMG_W && trfm.y < e->zbufferb[stp])
		{
			p = init_ixy(stp, drawy.start - 1);
			while (++p.y < drawy.end)
			{
				tex.y = calc_sprite_texy(e, spriteonscreen, s, p);
				get_img_color(&e->obj[s.tex], tex, &c);
				if ((c.red != 0 || c.blue != 0 || c.green != 0) && !s.hidden)
					draw_point(e, p, &c);
			}
		}
	}
}
