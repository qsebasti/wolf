/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 17:07:15 by squiquem          #+#    #+#             */
/*   Updated: 2018/07/24 15:25:06 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <sys/time.h>

void		get_timeframe(t_env *e)
{
	struct timeval	time;

	e->oldtime = e->time;
	gettimeofday(&time, NULL);
	e->time = time.tv_sec * 1000 + time.tv_usec / 1000;
	e->frametime = e->time - e->oldtime;
}

double		get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void		print_endtime(t_env *e)
{
	char	*t;

	t = ft_itoa(e->scrg.endtime);
	mlx_string_put(e->mlx, e->win, 3, 0, 0xffffff, "(ms) ");
	mlx_string_put(e->mlx, e->win, 53, 0, 0xffffff, t);
	free(t);
}

void		print_time(t_env *e)
{
	char	*t;

	t = ft_itoa((int)(e->time - e->start_time));
	mlx_string_put(e->mlx, e->win, 3, 0, 0xffffff, "(ms) ");
	mlx_string_put(e->mlx, e->win, 53, 0, 0xffffff, t);
	free(t);
}
