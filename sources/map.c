/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsebasti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 15:06:02 by qsebasti          #+#    #+#             */
/*   Updated: 2019/03/29 20:06:17 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	direction(t_point max, t_env *e)
{
	int		i;
	int		j;
	int		a;
	int		b;

	a = (int)e->pos.x * max.x / e->linelen + max.x / e->linelen / 2;
	b = (int)e->pos.y * max.y / e->nbline + max.x / e->nbline / 2;
	i = (int)e->pos.y * max.y / e->nbline - max.x / e->nbline / 2 - 1;
	while (++i < (int)e->pos.x * max.x / e->nbline + 2 * max.x / e->nbline)
	{
		j = (int)e->pos.x * max.x / e->linelen - max.x / e->linelen / 2 - 1;
		while (++j < (int)e->pos.x * max.x / e->linelen + 2 * max.x / e->linelen)
		{
			if (max.x > max.y)
			{
				if ((j - a) * (j - a) + (i - b) * (i - b) <= max.x / e->linelen * max.x / e->linelen)
					if (i < IMG_H && j > 0)
						*(int *)&e->pixel_img[j * (e->bpp / 8)
							+ (IMG_H - max.y + i) * e->s_line] = BLUE;
			}
			else
				if ((j - a) * (j - a) + (i - b) * (i - b) <= max.y / e->nbline * max.y / e->nbline)
					if (i < IMG_H && j > 0)
						*(int *)&e->pixel_img[j * (e->bpp / 8)
							+ (IMG_H - max.y + i) * e->s_line] = BLUE;
		}
	}
}

static void	player(t_point max, t_env *e)
{
	int		i;
	int		j;
	int		sizex;
	int		sizey;

	direction(max, e);
	sizex = max.x / e->linelen;
	sizey = max.y / e->nbline;
	i = (int)e->pos.y * sizey - 1;
	while (++i < (int)e->pos.y * sizey + sizey)
	{
		j = (int)e->pos.x * sizex - 1;
		while (++j < (int)e->pos.x * sizex + sizex)
				*(int *)&e->pixel_img[j * (e->bpp / 8) + (IMG_H - max.y + i)
					* e->s_line] = RED;
	}
}

static void	draw_walls(int x, int y, t_point max, t_env *e)
{
	int		i;
	int		j;
	int		sizex;
	int		sizey;

	sizex = max.x / e->linelen;
	sizey = max.y / e->nbline;
	i = y * sizey - 1;
	while (++i < y * sizey + sizey)
	{
		j = x * sizex - 1;
		while (++j < x * sizex + sizex)
		{
			if (e->door.x == x && e->door.y == y)
				*(int *)&e->pixel_img[j * (e->bpp / 8) + (IMG_H - max.y + i)
					* e->s_line] = WHITE;
			else
				*(int *)&e->pixel_img[j * (e->bpp / 8) + (IMG_H - max.y + i)
					* e->s_line] = DARK_GREY;
		}
	}
}

static void	draw_map(t_point max, t_env *e)
{
	int		i;
	int		j;

	i = -1;
	while (++i < e->nbline)
	{
		j = -1;
		while (++j < e->linelen)
		{
			if (e->worldmap[i][j] == 1 || e->worldmap[i][j] == 2)
				draw_walls(j, i, max, e);
		}
	}
}

void		map(t_env *e)
{
	int		i;
	int		j;
	t_point	max;

	max.x = 200;
	while (max.x % e->linelen != 0)
		max.x--;
	max.y = 200;
	while (max.y % e->nbline != 0)
		max.y--;
	i = -1;
	while (++i < max.y)
	{
		j = -1;
		while (++j < max.x)
			*(int *)&e->pixel_img[j * (e->bpp / 8) + (IMG_H - i) * e->s_line]
				= GREY;
	}
	draw_map(max, e);
	player(max, e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
//	exit(1);
}
