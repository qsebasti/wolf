/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsebasti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 17:10:18 by qsebasti          #+#    #+#             */
/*   Updated: 2018/09/05 22:51:45 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int					init_tab(t_tab **t)
{
	if (!(*t = (t_tab *)malloc(sizeof(t_tab))))
		print_error("Error malloc");
	(*t)->split = NULL;
	(*t)->len = -1;
	(*t)->listlen = 1;
	(*t)->next = NULL;
	return (0);
}

int					fillmap(t_tab *t, t_env *e)
{
	int i;
	int j;

	if (!(e->worldmap = (int **)malloc(sizeof(int *) * t->listlen)))
		print_error("Error malloc");
	i = -1;
	e->nbline = t->listlen;
	e->linelen = t->len;
	while (t)
	{
		++i;
		j = -1;
		if (!((e->worldmap)[i] = (int *)malloc(sizeof(int) * t->len)))
			print_error("Error malloc");
		while (++j < t->len)
			(e->worldmap)[i][j] = t->numb[j];
		t = t->next;
	}
	return (0);
}

void				freelist(t_tab *t)
{
	t_tab *tmp;

	while (t)
	{
		ft_freesplit(t->split);
		free(t->numb);
		tmp = t;
		t = t->next;
		free(tmp);
	}
}

int					checksquare(t_tab *t)
{
	int i;

	i = -1;
	while (++i < t->len)
		if (!t->numb[i])
			return (-1);
	i = -1;
	while (t)
	{
		if (!t->numb[0] || !t->numb[t->len - 1 % t->len])
			return (-1);
		if (!t->next)
			while (++i < t->len)
				if (!t->numb[i])
					return (-1);
		t = t->next;
	}
	return (0);
}
