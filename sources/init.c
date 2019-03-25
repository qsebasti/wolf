/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 17:07:15 by squiquem          #+#    #+#             */
/*   Updated: 2019/03/25 20:59:16 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*static int		check_same(int *randx, int *randy, int size)
  {
  int i;
  int tmp;

  i = -1;
  while (++i < size)
  {
  tmp = i;
  while (++tmp < size)
  if (randx[i] == randx[tmp] && randy[i] == randy[tmp])
  return (1);
  }
  return (0);
  }
*/

/*
**	Fonction tmp pour afficher la map dans le shell
*/

static void		print_pos(t_env *e, int *randx, int *randy)
{
/*	int i;
	int j;
	int	l;
	int	tmp[10];
	int toto;

	ft_memset(tmp, 0, 10 * sizeof(*tmp));
	i = -1;
	while (++i < 10)
		printf("randx[%d] = %d, randy[%d] = %d\n", i, randx[i], i, randy[i]);
	i = -1;
	while (++i < e->nbline)
	{
		j = -1;
		toto = 0;
		while (++j < e->linelen)
		{
			l = toto;
			while (randy[l] != i && l < 10)
			{
				l++;
			}
			if (randy[l] == i && l < 10)
				printf(" %d (%d) ", l, randx[l]);
			if (i == randy[l] && j == randx[l] && e->worldmap[i][j] == 0)
			{
				tmp[l] = 1;
				ft_putchar('S');
			}
			else if (e->worldmap[i][j] == 0)
				ft_putchar('.');
			else if (e->worldmap[i][j] == 1)
				ft_putchar('1');
			else if (e->worldmap[i][j] == 2)
				ft_putchar('2');
			ft_putchar(' ');
			toto = l + 1;
		}
		ft_putchar('\n');
	}
		ft_putchar('\n');
	i = -1;
	while (++i < 10)
		printf("%d\n", tmp[i]);*/
	char m[e->nbline + 1][e->linelen + 1];
	int i;
	int j;

	i = -1;
	while (++i < e->nbline)
	{
		j = -1;
		while (++j < e->linelen)
		{
			if ((int)e->pos.x == j && (int)e->pos.y == i)
				m[i][j] = 'P';
			else if (e->worldmap[i][j] == 0)
				m[i][j] = e->worldmap[i][j] + '.';
			else
				m[i][j] = e->worldmap[i][j] + '0';
		}
		m[i][j] = '\0';
	}
	i = -1;
	while (++i < 10)
		m[randy[i]][randx[i]] = 'S';
	i = -1;
	while (++i < e->nbline)
		ft_putendl(m[i]);
}

/*
**	Construction des deux tableaux aleatoires pour le placement des sprites
*/

static void		ft_rand(t_env *e, int *randx, int *randy, int size)
{
	int i;

	srand(time(NULL));
	i = -1;
	while (++i < size)
	{
		randx[i] = rand() % (e->linelen - 1) + 1;
		randy[i] = rand() % (e->nbline - 1) + 1;
	}
	i = -1;
	while (++i < size)
	{
		if (e->worldmap[randy[i]][randx[i]] == 1)
			while (e->worldmap[randy[i]][randx[i]] == 1)
			{
				randx[i] = rand() % (e->linelen - 1) + 1;
				randy[i] = rand() % (e->nbline - 1) + 1;
			}
		if (e->worldmap[randy[i]][randx[i]] == 0 && (randx[i] != (int)e->pos.x
				&& randy[i] != (int)e->pos.y))
		{
			if (free_spaces(e) > size * 2)
				while (!check_proxi2(e, randy[i], randx[i]))
				{
					randx[i] = rand() % (e->linelen - 1) + 1;
					randy[i] = rand() % (e->nbline - 1) + 1;
				}
		}
	}
}

/*
**	Placement des sprites
**	Sprites format: {x, y, tex, offset, scale, hidden, random, move_time}
*/

static void		init_sprites(t_env *e)
{
	int		randx[10];
	int		randy[10];
	int		i;

	ft_memset(randx, 0, 10 * sizeof(*randx));
	ft_memset(randy, 0, 10 * sizeof(*randy));
	if (free_spaces(e) > 10 * 3)
	{
		ft_rand(e, randx, randy, 10);
		i = 1;
		e->sprite[0] = init_sprite(randx[0], randy[0], 0, e);
		e->sprite[1] = init_sprite(randx[1], randy[1], 1, e);
		while (++i < 7)
			e->sprite[i] = init_sprite(randx[i], randy[i], 3, e);
		i--;
		while (++i < 10)
			e->sprite[i] = init_sprite(randx[i], randy[i], 5, e);
	}
	print_pos(e, randx, randy);
}

/*
**	Verification des 4 cases autour de la case souhaitee
*/

static t_dxy	place(t_env *e, int **map, int i, int j)
{
	t_dxy re;

	re = init_dxy(0, 0);
	if (!map[e->nbline / 2 - i][e->linelen / 2 - j])
		re = init_dxy(e->linelen / 2 - j + 0.5, e->nbline / 2 - i + 0.5);
	else if (!map[e->nbline / 2 - i][e->linelen / 2 + j])
		re = init_dxy(e->linelen / 2 + j + 0.5, e->nbline / 2 - i + 0.5);
	else if (!map[e->nbline / 2 + i][e->linelen / 2 + j])
		re = init_dxy(e->linelen / 2 + j + 0.5, e->nbline / 2 + i + 0.5);
	else if (!map[e->nbline / 2 + i][e->linelen / 2 - j])
		re = init_dxy(e->linelen / 2 - j + 0.5, e->nbline / 2 + i + 0.5);
	return (re);
}

/*
**	Definit la position de depart du personnage
*/

static t_dxy	start_pos(t_env *e)
{
	t_dxy	re;
	int		i;
	int		j;

	re = init_dxy(0, 0);
	i = 0;
	while (e->nbline / 2 - i > 0 && e->nbline / 2 + i < e->nbline - 1)
	{
		j = 0;
		while (e->linelen / 2 - j > 0 && e->linelen / 2 + j < e->linelen - 1)
		{
			re = place(e, e->worldmap, i, j);
			if (re.x && re.y)
				return (re);
			j++;
		}
		i++;
	}
	return (re);
}

/*
**	Initialisation des varables necessaires pour les calculs, sprites, positions
*/

void			init(t_env *e)
{
	//	e->door = init_ixy(0, 0);
	//	e->pos = init_dxy(e->nbline / 2, e->linelen / 2);
	e->pos = start_pos(e);
	printf("x %f y %f\n", e->pos.x, e->pos.y);
	e->dir = init_dxy(1, 0);
	e->plane = init_dxy(0, 0.66);
	e->oldtime = get_time();
	e->time = e->oldtime + 1;
	e->shoot_time = get_time();
	e->spritescreenx = 0;
	load_texture(e);
	init_sprites(e);
	e->bullet_start = 0;
	e->mouse.x = 0;
	e->mouse.y = WIN_W / 2;
	ft_bzero(&e->scrg, sizeof(e->scrg));
	e->scrg.ammo_available = AMMO;
	e->scrg.livingenemies = ENEMIES;
	ft_memset(e->key, 0, sizeof(e->key));
	ft_memset(&e->map, 0, sizeof(e->map));
}

/*
**	Fonction pour l'ecran de depart.
*/

void			start_screen(t_env *e)
{
	int h;
	int w;

	if (!(e->img = mlx_xpm_file_to_image(e->mlx, "pics/pokemon-ghost2.xpm", &w,\
					&h)))
		print_error("Error mlx");
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	mlx_string_put(e->mlx, e->win, WIN_W / 2 - 20, WIN_H / 2, 0xff0000,\
			"Press Enter");
}
