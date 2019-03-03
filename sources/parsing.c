/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsebasti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 17:10:18 by qsebasti          #+#    #+#             */
/*   Updated: 2018/07/19 16:02:49 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static t_tab			*new_link(t_tab *t)
{
	t_tab *tmp;

	while (t->next)
		t = t->next;
	if (!(tmp = (t_tab *)malloc(sizeof(t_tab))))
		return (NULL);
	tmp->split = NULL;
	tmp->len = -1;
	tmp->next = NULL;
	t->next = tmp;
	return (tmp);
}

static int				ft_splitlen(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

static int				add_link(t_tab **t, char *line)
{
	int		i;
	t_tab	*tmp;

	if ((*t)->split == NULL)
		tmp = *t;
	else
	{
		(*t)->listlen++;
		tmp = new_link(*t);
	}
	if (!(tmp->split = ft_strsplit(line, ' ')))
		print_error("Error malloc");
	tmp->len = ft_splitlen(tmp->split);
	if (!(tmp->numb = (int *)malloc(sizeof(int) * (tmp->len))))
		print_error("Error malloc");
	i = -1;
	while (tmp->split[++i])
		tmp->numb[i] = ft_atoi(tmp->split[i]);
	return (1);
}

static int				check_len(t_tab *t)
{
	int i;
	int j;
	int diff;

	diff = t->len;
	while (t)
	{
		i = -1;
		while (t->split[++i])
		{
			j = -1;
			while (t->split[i][++j])
				if (t->split[i][j] != '0' && t->split[i][j] != '1'
						&& t->split[i][j] != '2')
					return (0);
			if (t->numb[i] != 1 && t->numb[i] != 0 && t->numb[i] != 2)
				return (0);
		}
		if (i != diff)
			return (0);
		t = t->next;
	}
	return (1);
}

int						ft_read(char *av, t_env *e)
{
	char	*line;
	int		ret;
	t_tab	*t;
	int		fd;

	t = NULL;
	init_tab(&t);
	if ((fd = open(av, O_RDONLY)) == -1)
		print_error("Error open");
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		add_link(&t, line);
		if (!check_len(t))
			return (-1);
		free(line);
	}
	free(line);
	if (ret == -1 || t->split == NULL || close(fd) == -1
			|| checksquare(t) == -1)
		return (-1);
	fillmap(t, e);
	checkdoor(e);
	freelist(t);
	return (ret);
}
