/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 18:05:10 by squiquem          #+#    #+#             */
/*   Updated: 2019/02/20 20:30:43 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "keyboard.h"

static void	mouse_pointer(t_env *e)
{
	if (e->key[KEY_TAB] == 1)
		mlx_do_mouse_relativeoff(e->win);
	else
		mlx_do_mouse_relativeon(e->win);
}

static void	key_hook_move(t_env *e)
{
	if (e->key[KEY_UP] == 1 || e->key[KEY_W] == 1)
	{
		if (!(e->worldmap[(int)(e->pos.x + e->dir.x * LIM_W)][(int)e->pos.y])
				& !check_barrier(e, e->pos.x + e->dir.x * LIM_W, e->pos.y))
			e->pos.x += e->dir.x * SPEED;
		if (!(e->worldmap[(int)e->pos.x][(int)(e->pos.y + e->dir.y * LIM_W)])
				&& !check_barrier(e, e->pos.x, e->pos.y + e->dir.y * LIM_W))
			e->pos.y += e->dir.y * SPEED;
	}
	if (e->key[KEY_DOWN] == 1 || e->key[KEY_S] == 1)
	{
		if (!(e->worldmap[(int)(e->pos.x - e->dir.x * LIM_W)][(int)e->pos.y])
				& !check_barrier(e, e->pos.x - e->dir.x * LIM_W, e->pos.y))
			e->pos.x -= e->dir.x * SPEED;
		if (!(e->worldmap[(int)e->pos.x][(int)(e->pos.y - e->dir.y * LIM_W)])
				&& !check_barrier(e, e->pos.x, e->pos.y - e->dir.y * LIM_W))
			e->pos.y -= e->dir.y * SPEED;
	}
	if (e->key[KEY_SPC] == 1)
		printf("pos: %f %f\n", e->pos.x, e->pos.y);
}

static void	key_hook_turn(t_env *e)
{
	double	olddir;
	double	oldplane;

	olddir = e->dir.x;
	oldplane = e->plane.x;
	if (e->key[KEY_RIGHT] == 1 || e->key[KEY_D] == 1)
	{
		if (!(e->worldmap[(int)(e->pos.x - e->dir.y * LIM_W)][(int)e->pos.y])
				&& !check_barrier(e, e->pos.x - e->dir.x * LIM_W, e->pos.y))
			e->pos.x -= e->dir.y * SPEED;
		if (!(e->worldmap[(int)e->pos.x][(int)(e->pos.y + e->dir.x * LIM_W)])
				&& !check_barrier(e, e->pos.x, e->pos.y + e->dir.x * LIM_W))
			e->pos.y += e->dir.x * SPEED;
	}
	if (e->key[KEY_LEFT] == 1 || e->key[KEY_A] == 1)
	{
		if (!(e->worldmap[(int)(e->pos.x + e->dir.y * LIM_W)][(int)e->pos.y])
				&& !check_barrier(e, e->pos.x + e->dir.x * LIM_W, e->pos.y))
			e->pos.x += e->dir.y * SPEED;
		if (!(e->worldmap[(int)e->pos.x][(int)(e->pos.y - e->dir.x * LIM_W)])
				&& !check_barrier(e, e->pos.x, e->pos.y - e->dir.x * LIM_W))
			e->pos.y -= e->dir.x * SPEED;
	}
}

static void	key_hook_end(t_env *e)
{
	if (e->key[KEY_ESC] == 1)
	{
		mlx_destroy_window(e->mlx, e->win);
		exit(1);
	}
}

int			key_hook(t_env *e)
{
	key_hook_move(e);
	key_hook_turn(e);
	key_hook_end(e);
	mouse_pointer(e);
	return (0);
}
