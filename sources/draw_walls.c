/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 15:02:34 by squiquem          #+#    #+#             */
/*   Updated: 2019/03/25 19:46:01 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static t_img	choose_tex(t_env *e, t_dxy ray)
{
	t_img	teximg;

	if (e->worldmap[e->map.x][e->map.y] == 2)
		teximg = (e->scrg.score < ENEMIES ? e->tex[5] : e->tex[6]);
	else if (!e->side && ray.x > 0)
		teximg = e->tex[1];
	else if (!e->side && ray.x < 0)
		teximg = e->tex[2];
	else if (e->side && ray.y > 0)
		teximg = e->tex[3];
	else
		teximg = e->tex[4];
	return (teximg);
}

void			draw_textures(int x, t_sgmt draw, t_dxy ray, t_env *e)
{
	t_ixy	tex;
	t_ixy	p;
	t_img	teximg;
	t_color	c;

	teximg = choose_tex(e, ray);
	tex.x = (int)(e->wallx * (double)teximg.size.x);
	if ((!e->side && ray.x > 0) || (e->side && ray.y < 0))
		tex.x = teximg.size.x - tex.x - 1;
	p.y = ((draw.start > 0) ? draw.start - 1 : -1);
	p.x = x;
	while (++p.y < (draw.end < WIN_H ? draw.end : WIN_H))
	{
		tex.y = (p.y * 256 + (draw.end - draw.start - IMG_H) * 128)
				* teximg.size.y / (draw.end - draw.start) / 256;
		get_img_color(&teximg, tex, &c);
		draw_point(e, p, &c);
	}
}

static t_dxy	calc_currfloor(t_env *e, t_ixy p, t_dxy floorwall)
{
	t_dxy	currfloor;
	double	weight;

	weight = (IMG_H / (2.0 * p.y - IMG_H)) / e->perpwalldist;
	currfloor.x = weight * floorwall.x + (1.0 - weight) * e->pos.x;
	currfloor.y = weight * floorwall.y + (1.0 - weight) * e->pos.y;
	return (currfloor);
}

void			draw_ground(int x, t_sgmt draw, t_dxy ray, t_env *e)
{
	t_dxy	floorwall;
	t_dxy	currfloor;
	t_ixy	p;
	t_ixy	floortex;
	t_color	c;

	floorwall = calc_floorwall(e, ray);
	if (draw.end < 0)
		draw.end = IMG_H;
	p.x = x;
	p.y = draw.end;
	while (++p.y < IMG_H)
	{
		currfloor = calc_currfloor(e, p, floorwall);
		floortex.x = (int)(currfloor.x * e->tex[10].size.x) % e->tex[10].size.x;
		floortex.y = (int)(currfloor.y * e->tex[10].size.y) % e->tex[10].size.y;
		get_img_color(&e->tex[10], floortex, &c);
		draw_point(e, p, &c);
		draw_ceiling(p, currfloor, e);
	}
}

void			draw_ceiling(t_ixy p, t_dxy currfloor, t_env *e)
{
	t_ixy	q;
	t_color	c;
	t_ixy	floortex;

	floortex.x = (int)(currfloor.x * e->tex[9].size.x) % e->tex[9].size.x;
	floortex.y = (int)(currfloor.y * e->tex[9].size.y) % e->tex[9].size.y;
	q = init_ixy(p.x, IMG_H - p.y);
	get_img_color(&e->tex[9], floortex, &c);
	draw_point(e, q, &c);
}
