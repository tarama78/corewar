/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 16:10:40 by tnicolas          #+#    #+#             */
/*   Updated: 2018/02/09 20:50:45 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**   ____________________________________________________________
**   | main.c                                                   |
**   ------------------------------------------------------------
**           __n__n__  /
**    .------`-\00/-'/
**   /  ##  ## (oo)
**  / \## __   ./
**     |//YY \|/
**     |||   |||
*/

/*
**	init:
**		initscr();
**		start_color();
**
**	couleur:
**		start_color(); //init
**		pair de couleur:
**			init_pair();
**			attron();
**			wattron();
**
**	close:
**		endwin();
**
**	refresh:
**		refresh(); // refresh la fenetre
**		wrefresh(win);
**		clear();   // clear la fenetre
**
**	printf:
**		printw(const char *format, ...);
**		mvprintw(line, col, "format", ...);
**
**	scanf:
**		getch();
**			27 echap
**			410 redimentionnement
**			char ascii
**
**	move cursor:
**		move(ligne, colonne);
**			LINES=nb_line
**			COLS=nb_col
**
** 	ajouter char:
**		addch('c');
**		mvaddch(line, col, 'c');
**
**	mise en forme:
**		attron(mode);  //attron(A_BOLD | A_INVIS);
**		attrset(mode); //pareil mais en different
**			Normal (A_NORMAL)
**			Meilleur surlignement (A_STANDOUT)
**			Inversion vidéo (A_REVERSE)
**			À moitié brillant (A_DIM)
**			Très brillant ou en gras (A_BOLD)
**			Souligné (A_UNDERLINE)
**			Mode invisible ou blanc (A_INVIS)
**
**	sous fenetres:
**		subwin(stdstr, w, h, x, y); -> return un WINDOW*
**		bordure:
**			box(WINDOW*, ACS_VLINES, ACS_HLINES);
**				// les marcos ACS_VLINES sont trouvable ds le man
**			wborder(boite, '|', '|', '-', '-', '+', '+', '+', '+');
**			wrefresh(boite);
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include <ncurses.h>
#include <curses.h>
#include <libft.h>
#include <math.h>
#include "../commun/includes/op.h"
#include "../corewar/includes/corewar.h"

#define NB_COLORS 6

static t_color	ft_init_color()
{
	t_color	c;
	int		i;
	int		start_i;
	static int	colors[NB_COLORS] = {COLOR_GREEN, COLOR_YELLOW, COLOR_MAGENTA,
		COLOR_BLUE, COLOR_RED, COLOR_CYAN};

	init_pair(1, COLOR_WHITE, COLOR_WHITE);
	c.border = COLOR_PAIR(1) | A_STANDOUT;
	init_pair(2, COLOR_BLACK, COLOR_BLACK);
	c.black = COLOR_PAIR(2);
	init_pair(3, COLOR_WHITE, COLOR_BLACK);
	c.defaut = COLOR_PAIR(3);

	c.player[0] = c.defaut;
	start_i = 10;
	i = 0;
	while (++i < MAX_PLAYERS)
	{
		init_pair(start_i + i, colors[(i - 1) % NB_COLORS], COLOR_BLACK);
		c.player[i] = COLOR_PAIR(start_i + i);
	}
	return (c);
}

static void	ft_init(t_a *a)
{
	a->nc.win_mem = NULL;
	a->nc.win_info = NULL;
	initscr();
	start_color();
	noecho();
	curs_set(0);
	a->nc.color = ft_init_color();
	a->nc.sqrt_mem_size = sqrt(MEM_SIZE);
	a->nc.win_mem = subwin(stdscr, a->nc.sqrt_mem_size + 3, a->nc.sqrt_mem_size * 3 + 5, 0, 0);
}

static void	ft_print_memory(t_a *a)
{
	int		i;
	int		j;
	int		k;

	i = 1;
	k = 0;
	while (++i < a->nc.sqrt_mem_size + 1)
	{
		j = 0;
		while ((j += 3) < a->nc.sqrt_mem_size * 3 + 1)
		{
			wattron(a->nc.win_mem, a->nc.color.player[a->mem_color[k] % MAX_PLAYERS]);
			mvwprintw(a->nc.win_mem, i, j, "%02hhx", a->mem[k]);
			wattroff(a->nc.win_mem, a->nc.color.player[a->mem_color[k]] % MAX_PLAYERS);
			if (j + 2 <= a->nc.sqrt_mem_size)
			{
				wattron(a->nc.win_mem, a->nc.color.black);
				mvwprintw(a->nc.win_mem, i, j + 2, " ");
				wattroff(a->nc.win_mem, a->nc.color.black);
			}
			k++;
		}
	}
}

static void	ft_exec(t_a *a)
{
	wattron(a->nc.win_mem, a->nc.color.border);
	wborder(a->nc.win_mem, '|', '|', '-', '-', '+', '+', '+', '+');
	wattroff(a->nc.win_mem, a->nc.color.border);
	wrefresh(a->nc.win_mem);

//	wattron(a->nc.win_mem, a->nc.color.red);
//	mvwprintw(a->nc.win_mem, 5, 5, "seksek");
//	wattroff(a->nc.win_mem, a->nc.color.red);
//
//	wattron(a->nc.win_mem, a->nc.color.blue);
//	mvwprintw(a->nc.win_mem, 6, 5, "seksek");
//	wattroff(a->nc.win_mem, a->nc.color.blue);
	///////////////////////////////////////////////////
	ft_memset(a->mem, 0, MEM_SIZE);
	int		i = -1;
	while (++i < MEM_SIZE)
		a->mem[i] = i % 256;
	ft_memset(a->mem_color, 0, MEM_SIZE);
	i = -1;
	while (++i < MEM_SIZE / 4)
		a->mem_color[i] = 1;
	i = (MEM_SIZE >> 1) - 1;
	while (++i < MEM_SIZE / 4 + (MEM_SIZE >> 1))
		a->mem_color[i] = 2;
	///////////////////////////////////////////////////
	ft_print_memory(a);
	refresh();
	while (getch() != 27)
		;
}

int			main(int ac, char **av)
{
	t_a		a;

	(void)ac;
	(void)av;
	ft_init(&a);
	ft_exec(&a);
	ft_fruit(2, &a.nc.win_mem, &a.nc.win_info);
	endwin();
	return (0);
}
