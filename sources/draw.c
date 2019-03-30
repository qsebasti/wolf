/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 00:34:11 by squiquem          #+#    #+#             */
/*   Updated: 2019/03/30 12:03:36 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "keyboard.h"
#include <string.h>
#include <errno.h>

static void		draw_wall_line(int x, t_env *e)
{
	t_sgmt	draw;
	t_dxy	ray;
	t_dxy	sidedist;
	t_ixy	step;

	e->map = init_ixy((int)e->pos.x, (int)e->pos.y);
	e->side = 0;
	ray = init_dxy(e->dir.x + e->plane.x * (2 * x / (double)IMG_W - 1),
		e->dir.y + e->plane.y * (2 * x / (double)IMG_W - 1));
	step = calc_step(ray);
	sidedist = calc_sidedist(ray, e);
	e->perpwalldist = calc_wall_size(sidedist, ray, step, e);
	e->zbuffer[x] = e->perpwalldist;
	e->zbufferb[x] = e->perpwalldist;
	draw = init_sgmt((IMG_H - (int)(IMG_H / e->perpwalldist)) / 2,
		(IMG_H + (int)(IMG_H / e->perpwalldist)) / 2);
	e->wallx = ((e->side) ? (e->pos.x + e->perpwalldist * ray.x)
			: (e->pos.y + e->perpwalldist * ray.y));
	e->wallx -= floor(e->wallx);
	draw_textures(x, draw, ray, e);
	draw_ground(x, draw, ray, e);
}

static void		draw(t_env *e)
{
	int		i;

	if (!(e->pixel_img = mlx_get_data_addr(e->img, &(e->bpp)
					, &(e->s_line), &(e->ed))))
		print_error("Error mlx");
	i = -1;
	while (++i < IMG_W)
		draw_wall_line(i, e);
	get_timeframe(e);
	draw_sprites(e);
	if (e->bullet_start)
		draw_bullet(e);
}

int				reload(t_env *e)
{
	key_hook(e);
	mlx_clear_window(e->mlx, e->win);
	if (e->key[KEY_ENTER] != 1)
	{
		start_screen(e);
		return (0);
	}
	draw(e);
	win(e);
	end_screen(e);
	hud(e);
	return (0);
}
