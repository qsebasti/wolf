/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 00:34:11 by squiquem          #+#    #+#             */
/*   Updated: 2019/03/25 19:46:37 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

t_ixy		calc_step(t_dxy ray)
{
	t_ixy	step;

	step.x = (ray.x < 0 ? -1 : 1);
	step.y = (ray.y < 0 ? -1 : 1);
	return (step);
}

t_dxy		calc_sidedist(t_dxy ray, t_env *e)
{
	t_dxy	sidedist;
	t_dxy	deltadist;

	deltadist = init_dxy(fabs(1 / ray.x), fabs(1 / ray.y));
	(ray.x < 0) ? (sidedist.x = (e->pos.x - e->map.x) * deltadist.x)
		: (sidedist.x = (e->map.x + 1.0 - e->pos.x) * deltadist.x);
	(ray.y < 0) ? (sidedist.y = (e->pos.y - e->map.y) * deltadist.y)
		: (sidedist.y = (e->map.y + 1.0 - e->pos.y) * deltadist.y);
	return (sidedist);
}

double		calc_wall_size(t_dxy sidedist, t_dxy ray, t_ixy step, t_env *e)
{
	double	perpwalldist;
	int		hit;

	hit = 0;
	while (!hit)
	{
		(sidedist.x < sidedist.y) ? (e->map.x += step.x)
			: (e->map.y += step.y);
		e->side = (sidedist.x < sidedist.y ? 0 : 1);
		(sidedist.x < sidedist.y) ?
			(sidedist.x += fabs(1 / ray.x)) : (sidedist.y += fabs(1 / ray.y));
		if (e->worldmap[e->map.x][e->map.y] > 0)
			hit = 1;
	}
	perpwalldist = ((!e->side)
			? ((e->map.x - e->pos.x + (1 - step.x) / 2) / ray.x)
			: ((e->map.y - e->pos.y + (1 - step.y) / 2) / ray.y));
	return (perpwalldist);
}

t_dxy		calc_floorwall(t_env *e, t_dxy ray)
{
	t_dxy	floorwall;

	if (e->side == 0 && ray.x > 0)
		floorwall = init_dxy(e->map.x, e->map.y + e->wallx);
	else if (e->side == 0 && ray.x < 0)
		floorwall = init_dxy(e->map.x + 1.0, e->map.y + e->wallx);
	else if (e->side == 1 && ray.y > 0)
		floorwall = init_dxy(e->map.x + e->wallx, e->map.y);
	else
		floorwall = init_dxy(e->map.x + e->wallx, e->map.y + 1.0);
	return (floorwall);
}
