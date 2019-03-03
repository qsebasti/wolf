/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkdoor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsebasti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 19:04:49 by qsebasti          #+#    #+#             */
/*   Updated: 2018/09/05 23:08:48 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int				free_spaces(t_env *e)
{
	int i;
	int j;
	int nb;

	nb = 0;
	i = -1;
	while (++i < e->nbline)
	{
		j = -1;
		while (++j < e->linelen)
			if (e->worldmap[i][j] == 0)
				nb++;
	}
	return (nb);
}

t_dxy			new_door(int **tab, int i, int j)
{
	t_dxy ret;

	ret = (t_dxy){0, 0};
	if (tab[i][j - 1] == 0)
		ret = (t_dxy){i, j - 1};
	else if (tab[i][j + 1] == 0)
		ret = (t_dxy){i, j + 1};
	else if (tab[i + 1][j] == 0)
		ret = (t_dxy){i + 1, j};
	else if (tab[i - 1][j] == 0)
		ret = (t_dxy){i - 1, j};
	return (ret);
}

int				check_proxi2(t_env *e, int i, int j)
{
	int nb;

	nb = 0;
	if (j - 1 > 0 && e->worldmap[i][j - 1] == 0)
		nb++;
	if (j + 1 < e->linelen && e->worldmap[i][j + 1] == 0)
		nb++;
	if (i - 1 > -1 && e->worldmap[i - 1][j] == 0)
		nb++;
	if (i + 1 < e->nbline && e->worldmap[i + 1][j] == 0)
		nb++;
	if (i - 1 > -1 && j + 1 < e->linelen && e->worldmap[i - 1][j + 1] == 0)
		nb++;
	if (i - 1 > -1 && j - 1 > 0 && e->worldmap[i - 1][j - 1] == 0)
		nb++;
	if (i + 1 < e->nbline && j + 1 < e->linelen\
			&& e->worldmap[i + 1][j + 1] == 0)
		nb++;
	if (i + 1 < e->nbline && j - 1 > 0 && e->worldmap[i + 1][j - 1] == 0)
		nb++;
	if (nb != 8)
		return (0);
	return (1);
}

static int		check_proxi(t_env *e, int i, int j)
{
	int nb;

	nb = 0;
	if (e->worldmap[i][j - 1] == 1)
		nb++;
	if (e->worldmap[i][j + 1] == 1)
		nb++;
	if (i - 1 > -1 && e->worldmap[i - 1][j] == 1)
		nb++;
	if (i + 1 < e->nbline && e->worldmap[i + 1][j] == 1)
		nb++;
	if (nb != 3)
	{
		e->worldmap[i][j] = 1;
		return (0);
	}
	return (1);
}

void			checkdoor(t_env *e)
{
	int count;
	int i;
	int j;

	count = 0;
	i = -1;
	while (++i < e->nbline)
	{
		j = -1;
		while (++j < e->linelen)
		{
			if (e->worldmap[i][j] == 2)
			{
				count++;
				if (i != 0 && i != e->nbline - 1 && j != 0
						&& j != e->linelen - 1)
					if (!(check_proxi(e, i, j)))
						count--;
				if (count == 1 && e->door.x == 0 && e->door.y == 0)
				{
					e->door = (t_ixy){i, j};
					printf("porte : %d, %d\n", i, j);
				}
				else
					e->worldmap[i][j] = 1;
			}
		}
	}
}
