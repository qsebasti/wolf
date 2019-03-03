/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 17:07:15 by squiquem          #+#    #+#             */
/*   Updated: 2018/09/05 23:34:12 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	open_texture(t_env *e, t_img *tex, char *name)
{
	if (!(tex->img = mlx_xpm_file_to_image(e->mlx, name, &tex->size.x,\
					&tex->size.y)))
		print_error("Error mlx");
	if (!(tex->pixel_img = mlx_get_data_addr(tex->img, &tex->bpp, &tex->s_line,
					&tex->ed)))
		print_error("Error mlx");
}

void	load_texture(t_env *e)
{
	open_texture(e, &e->tex[0], "pics/colorstone.xpm");
	open_texture(e, &e->tex[1], "pics/wood.xpm");
	open_texture(e, &e->tex[2], "pics/redbrick.xpm");
	open_texture(e, &e->tex[3], "pics/greystone.xpm");
	open_texture(e, &e->tex[4], "pics/mossy.xpm");
	open_texture(e, &e->tex[5], "pics/door.xpm");
	open_texture(e, &e->tex[6], "pics/door-open.xpm");
	open_texture(e, &e->tex[7], "pics/day.xpm");
	open_texture(e, &e->tex[8], "pics/sky-toon.xpm");
	open_texture(e, &e->tex[9], "pics/floor.xpm");
	open_texture(e, &e->tex[10], "pics/ceiling.xpm");
	open_texture(e, &e->tex[11], "pics/night.xpm");
	open_texture(e, &e->obj[0], "pics/barrel.xpm");
	open_texture(e, &e->obj[1], "pics/pillar.xpm");
	open_texture(e, &e->obj[2], "pics/greenlight.xpm");
	open_texture(e, &e->obj[3], "pics/pokeballblack.xpm");
	open_texture(e, &e->obj[4], "pics/pokeballblack.xpm");
	open_texture(e, &e->obj[5], "pics/fantominus.xpm");
}

void	get_img_color(t_img *tex, t_ixy p, t_color *c)
{
	if (p.x >= 0 && p.x < tex->size.x && p.y >= 0 && p.y < tex->size.y)
	{
	c->red = tex->pixel_img[p.y * tex->s_line + p.x * (tex->bpp / 8)];
	c->green = tex->pixel_img[p.y * tex->s_line + p.x * (tex->bpp / 8) + 1];
	c->blue = tex->pixel_img[p.y * tex->s_line + p.x * (tex->bpp / 8) + 2];
	}
}

void	draw_point(t_env *e, t_ixy p, t_color *c)
{
	if (p.x >= 0 && p.x < WIN_W && p.y >= 0 && p.y < WIN_H)
	{
		e->pixel_img[p.y * e->s_line + p.x * (e->bpp / 8)] = c->red;
		e->pixel_img[p.y * e->s_line + p.x * (e->bpp / 8) + 1] = c->green;
		e->pixel_img[p.y * e->s_line + p.x * (e->bpp / 8) + 2] = c->blue;
	}
}

void	put_point(t_env *e, int x, int y, int color)
{
	if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
		*((int *)&(e->pixel_img[x * (e->bpp / 8) + y * e->s_line])) = color;
}
