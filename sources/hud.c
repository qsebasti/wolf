/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsebasti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 15:46:20 by qsebasti          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:22 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		hud_minia(t_ixy drawy, t_env *e, t_img s, t_ixy start)
{
	int		stp;
	t_ixy	p;
	t_ixy	tex;
	t_color	c;

	(void)drawy;
	stp = start.x - 1;
	while (++stp < start.x + drawy.x)
	{
		tex.x = stp - start.x;
		p = init_ixy(stp, start.y - 1);
		while (++p.y < start.y + drawy.y)
		{
			tex.y = p.y - start.y;
			get_img_color(&s, tex, &c);
			if (c.red != 0 || c.blue != 0 || c.green != 0)
				draw_point(e, p, &c);
		}
	}
}

static void		init_minia(t_env *e)
{
	t_img	s[2];
	t_ixy	drawy;
	t_ixy	start;
	int		i;

	s[0].img = mlx_xpm_file_to_image(e->mlx, "pics/pokeballblackmini.xpm",
			&s[0].size.x, &s[0].size.y);
	if (!(s[0].pixel_img = mlx_get_data_addr(s[0].img, &s[0].bpp, &s[0].s_line,
					&s[0].ed)))
		print_error("Error mlx");
	s[1].img = mlx_xpm_file_to_image(e->mlx, "pics/minifantominus.xpm",
			&s[1].size.x, &s[1].size.y);
	if (!(s[1].pixel_img = mlx_get_data_addr(s[1].img, &s[1].bpp, &s[1].s_line,
					&s[1].ed)))
		print_error("Error mlx");
	i = -1;
	while (++i < 2)
	{
		start = init_ixy(WIN_W - 135 + i * 20, WIN_H - 155 + i * 80);
		drawy = init_ixy(s[i].size.x, s[i].size.y);
		hud_minia(drawy, e, s[i], start);
	}
}

static void		hud_sights(t_env *e)
{
	int i;

	i = -1;
	while (++i < 21)
		put_point(e, WIN_W / 2 - 10 + i, WIN_H / 2, SNOW);
	i = -1;
	while (++i < 21)
		put_point(e, WIN_W / 2 - 10 + i, WIN_H / 2 - 1, SNOW);
	i = -1;
	while (++i < 21)
		put_point(e, WIN_W / 2 - 10 + i, WIN_H / 2 + 1, SNOW);
	i = -1;
	while (++i < 21)
		put_point(e, WIN_W / 2 - 1, WIN_H / 2 - 10 + i, SNOW);
	i = -1;
	while (++i < 21)
		put_point(e, WIN_W / 2 + 1, WIN_H / 2 - 10 + i, SNOW);
	i = -1;
	while (++i < 21)
		put_point(e, WIN_W / 2, WIN_H / 2 - 10 + i, SNOW);
}

void			hud(t_env *e)
{
	char *aff[2];

	if (e->scrg.end_status == VICTORY)
	{
		mlx_string_put(e->mlx, e->win, WIN_W / 2 - 20, WIN_H / 2, 0xff0000,\
				"You win");
		return ;
	}
	if (e->scrg.end_status == ULOSE)
	{
		mlx_string_put(e->mlx, e->win, WIN_W / 2 - 20, WIN_H / 2, 0xff0000,\
				"You lose");
		return ;
	}
	init_minia(e);
	hud_sights(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	map(e);
	print_time(e);
	aff[0] = ft_itoa(e->scrg.ammo);
	aff[1] = ft_itoa(e->scrg.livingenemies);
	mlx_string_put(e->mlx, e->win, WIN_W - 50, WIN_H - 115, 0xff0000, aff[0]);
	mlx_string_put(e->mlx, e->win, WIN_W - 50, WIN_H - 50, 0xff0000, aff[1]);
	free(aff[0]);
	free(aff[1]);
}
