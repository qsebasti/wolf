/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 00:34:11 by squiquem          #+#    #+#             */
/*   Updated: 2019/02/22 17:00:11 by qsebasti         ###   ########.fr       */
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

	e->map = (t_ixy){(int)e->pos.x, (int)e->pos.y};
	e->side = 0;
	ray = (t_dxy){e->dir.x + e->plane.x * (2 * x / (double)IMG_W - 1),
		e->dir.y + e->plane.y * (2 * x / (double)IMG_W - 1)};
	step = calc_step(ray);
	sidedist = calc_sidedist(ray, e);
	e->perpwalldist = calc_wall_size(sidedist, ray, step, e);
	e->zbuffer[x] = e->perpwalldist;
	e->zbufferb[x] = e->perpwalldist;
	draw = (t_sgmt){(IMG_H - (int)(IMG_H / e->perpwalldist)) / 2,
		(IMG_H + (int)(IMG_H / e->perpwalldist)) / 2};
	e->wallx = ((e->side) ? (e->pos.x + e->perpwalldist * ray.x)
			: (e->pos.y + e->perpwalldist * ray.y));
	e->wallx -= floor(e->wallx);
	draw_textures(x, draw, ray, e);
	draw_ground(x, draw, ray, e);
}

static void		*draw(void *e)
{
	int			x;
	t_sgmt		thread;
	t_th		*th;

	th = (t_th *)e;
	thread.end = (th->nb + 1) * IMG_W / NB_THR;
	thread.start = th->nb * IMG_W / NB_THR;
	x = thread.start - 1;
	while (++x < thread.end)
		draw_wall_line(x, th->env);
	get_timeframe(th->env);
	draw_sprites(th->env);
	if (th->env->bullet_start)
		draw_bullet(th->env);
	pthread_exit(NULL);
}

static void		thread(t_env *e)
{
	int		i;
	int		rc;
	t_th	th[NB_THR];

	if (!(e->img = mlx_new_image(e->mlx, IMG_W, IMG_H))
			|| !(e->pixel_img = mlx_get_data_addr(e->img, &(e->bpp)
					, &(e->s_line), &(e->ed))))
		print_error("Error mlx");
	i = -1;
	while (++i < NB_THR)
	{
		th[i].nb = i;
		th[i].env = e;
		if ((rc = pthread_create(&e->thr[i], NULL, draw, &th[i])))
			ft_putendl_fd(strerror(errno), 2);
	}
	i = -1;
	while (++i < NB_THR)
		if (pthread_join(e->thr[i], NULL))
			ft_putendl_fd(strerror(errno), 2);
}

int				reload(t_env *e)
{
	key_hook(e);
	if (e->key[KEY_ENTER] != 1)
	{
		start_screen(e);
		return (0);
	}
	thread(e);
	win(e);
	end_screen(e);
	hud(e);
	mlx_destroy_image(e->mlx, e->img);
	return (0);
}
