/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 19:09:49 by squiquem          #+#    #+#             */
/*   Updated: 2019/02/21 22:07:54 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# include <stdio.h>

# define MAPW				24
# define MAPH				24
# define WIN_H				720
# define WIN_W				1080
# define IMG_H				720
# define IMG_W				1080
# define NB_THR				1
# define SPEED				0.2
# define LIM_W				0.5
# define ROTCOS				0.866 //M_PI / 6
# define ROTSIN				0.5
# define AMMO				5
# define ENEMIES			3
# define OBJ				2
# define NUMSPRITES			AMMO + ENEMIES + OBJ
# define VICTORY			1
# define ULOSE				2

# define KPRESSMASK			1L << 0
# define KRELEASEMASK		1L << 1
# define BPRESSMASK			1L << 2
# define BRELEASEMASK		1L << 3
# define PTR_MOTION_MASK	1L << 6
# define SNOTIFYMASK		1L << 17
# define KPRESS				2
# define KRELEASE			3
# define BPRESS				4
# define BRELEASE			5
# define MOTION_NOTIFY		6
# define DESTROY			17

# define BLUE				0x0000cc
# define GREEN				0x00cc00
# define BROWN				0xcc6600
# define GRAY				0x999999
# define FUSHIA				0xcc00cc
# define YELLOW				0xcccc00
# define CYAN				0xccffff
# define WHITE				0xffffff
# define RED				0xff0000
# define SNOW				0xfffafa

typedef struct		s_ixy
{
	int				x;
	int				y;
}					t_ixy;

typedef struct		s_dxy
{
	double			x;
	double			y;
}					t_dxy;

typedef struct		s_sgmt
{
	int				start;
	int				end;
}					t_sgmt;

typedef struct		s_color
{
	int				red;
	int				green;
	int				blue;
}					t_color;

typedef struct		s_img
{
	void			*img;
	char			*pixel_img;
	int				bpp;
	int				s_line;
	int				ed;
	t_ixy			size;
}					t_img;

typedef struct		s_sprite
{
	double			x;
	double			y;
	int				tex;
	int				offset;
	int				scale;
	int				hidden;
	int				random;
	double			move_time;
}					t_sprite;

typedef struct		s_bullet
{
	t_sprite		sprite;
	t_dxy			dir;
	t_dxy			pos;
}					t_bullet;

/*typedef struct		s_calc
{
	int				side;
	double			wallx;
	t_ixy			map;
	t_dxy			ray;
	t_ixy			draw;
}					t_calc;*/

typedef struct		s_scoring
{
	int				score;
	int				end_status;
	int				ammo;
	int				ammo_available;
	int				livingenemies;
	int				endtime;
}					t_scoring;

typedef struct		s_mouse
{
	int				button;
	int				x;
	int				y;
}					t_mouse;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	t_img			tex[12];
	t_img			obj[6];
	void			*img;
	char			*pixel_img;
	int				bpp;
	int				s_line;
	int				ed;
	int				**worldmap;
	int				linelen;
	int				nbline;
	int				key[300];
	t_mouse			mouse;
	t_dxy			pos;
	t_dxy			dir;
	t_dxy			plane;
	t_ixy			map;
	int				side;
	double			wallx;
	double			perpwalldist;
	int				spritescreenx;
	double			zbuffer[IMG_W];				//sprites
	double			zbufferb[IMG_W];			//bullet
	t_sprite		sprite[NUMSPRITES];			//sprites
	int				spritesorder[NUMSPRITES];	//sprites
	double			spritesdistance[NUMSPRITES];//sprites
	int				bullet_start;
	t_bullet		bullet;
//	int				score;
//	int				end_status;
//	int				ammo;
//	int				ammo_available;
	t_scoring		scrg;
	t_ixy			door;
	double			time;
	double			start_time;
	double			oldtime;
	double			frametime;
	double			shoot_time;
	pthread_t		thr[NB_THR];
}					t_env;

typedef struct		s_th
{
	int				nb;
	t_env			*env;
}					t_th;

/*
**  Structure de parsing.
*/ 

typedef struct		s_tab
{
	char			**split;
	int				*numb;
	int				len;
	int				listlen;
	struct s_tab	*next;
}					t_tab;

int					key_hook(t_env *e);
int					keypress(int keycode, t_env *e);
int					keyrelease(int keycode, t_env *e);
int					mousehook(int x, int y, t_env *e);
int					check_barrier(t_env *e, double x, double y);

int					quit(void);
void				print_error(char*cause);

int					reload(t_env *e);

t_ixy				calc_step(t_dxy ray);
t_dxy				calc_sidedist(t_dxy ray, t_env *e);
double				calc_wall_size(t_dxy sidedist, t_dxy ray, t_ixy step,
					t_env *e);
int					calc_side(t_dxy sidedist, t_dxy ray, t_ixy step, t_env *e);
t_dxy				calc_floorwall(t_env *e, t_dxy ray);

void				draw_point(t_env *img, t_ixy p, t_color *c);
void				draw_textures(int x, t_sgmt draw, t_dxy ray, t_env *e);
void				draw_sky(int x, t_sgmt draw, t_env *e);
void				draw_ground(int x, t_sgmt draw, t_dxy ray, t_env *e);
void				draw_ceiling(t_ixy p, t_dxy currfloor, t_env *e);

void				open_texture(t_env *e, t_img *tex, char *name);
void				load_texture(t_env *e);
void				get_img_color(t_img *tex, t_ixy p, t_color *c);

void				draw_sprites(t_env *e);
void				sprite_sort(t_env *e);
void				pick_up(t_sprite *spri, t_env *e);
void				ft_combsort(int *order, double *dist, int amount);

void				init(t_env *e);

double				get_time(void);
void				get_timeframe(t_env *e);
void				print_time(t_env *e);
void				print_endtime(t_env *e);

int					ft_read(char *av, t_env *e);
int					init_tab(t_tab **t);
int					fillmap(t_tab *t, t_env *e);
void				freelist(t_tab *t);
int					checksquare(t_tab *t);
void				checkdoor(t_env *e);

void				draw_bullet(t_env *e);
int					key_hook_shoot(int button, int x, int y, t_env *e);

void				win(t_env *e);
void				lose(t_env *e, t_sprite s);
int					close_enough(t_dxy a, t_dxy b, double d);
void				rotate(t_env *e);

void				move_enemy(t_env *e, t_sprite *s, int r);
void				choose_direction(t_env *e, t_sprite *s);

t_ixy				calc_spriteonscreen(t_sprite spr, t_dxy trfm);
void				stripe_loop(t_sgmt dray, t_ixy spriteonscreen,
					t_env *e, t_sprite s);
void				stripe_loop_bullet(t_sgmt dray, t_ixy spriteonscreen,
					t_env *e, t_sprite s);
int					calc_stripe_texy(t_env *e, t_ixy spriteonscreen,
					t_sprite spr, t_ixy p);
t_dxy				calc_trfm(t_env *e, t_sprite spr);

void				start_screen(t_env *e);
void				end_screen(t_env *e);
void				hud(t_env *e);
t_dxy				new_door(int **tab, int i, int j);
void				put_point(t_env *e, int x, int y, int color);
int					free_spaces(t_env *e);
int					check_proxi2(t_env *e, int i, int j);
#endif
