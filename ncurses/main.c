/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 16:10:40 by tnicolas          #+#    #+#             */
/*   Updated: 2018/02/10 15:48:59 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                     __      ___                            */
/*                                     \ \    / (_)                           */
/*                ___  ___ _ __ __ _  __\ \  / / _ _ __ ___                   */
/*               / __|/ _ \ '__/ _` |/ _ \ \/ / | | '_ ` _ \                  */
/*               \__ \  __/ | | (_| |  __/\  /  | | | | | | |                 */
/*               |___/\___|_|  \__, |\___| \/   |_|_| |_| |_|                 */
/*                              __/ |                                         */
/*                             |___/                                          */
/*                                                                            */
/* ************************************************************************** */

/*
**   ____________________________________________________________
**   | main.c                                                   |
**   |     ft_init(9 lines)                                     |
**   |     ft_print_memory(28 lines)                            |
**   |         MEUUUU too many lines                            |
**   |     ft_exec(43 lines)                                    |
**   |         MEUUUU too many lines                            |
**   |     main(9 lines)                                        |
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

#include "../commun/includes/op.h"
#include "../corewar/includes/corewar.h"

//int		termfd;

static void	ft_exec(t_a *a)
{
	int		ch;

	ft_init(a);
	ft_print(a);
	while ((ch = getch()) != 27)
	{
		/////////////////////////////////////
		a->mem_info[ch].process = 1;
		a->mem_info[ch].player_process = 1;
		a->cycle = ch;
		/////////////////////////////////////
		ft_print(a);
		usleep(50);
	}
	ft_free_nc(a);
}

int			main(int ac, char **av)
{
	t_a		a;
	int		i;

//	termfd = open("/dev/ttys003", O_RDWR);
	(void)ac;
	(void)av;
	ft_strcpy(a.player[0].name, "percevaliodfhodhgjkhfdsjkhgjkdlshgljkdfhglkjsdhjkgdhfsjkghdsjklghlkjsdfhgfdjkls");
	ft_strcpy(a.player[1].name, "serge");
	ft_strcpy(a.player[2].name, "seksek");
	a.cycle = 0;
	a.num_of_player = 2;
	ft_memset(a.mem, 0, MEM_SIZE);
	i = -1;
	while (++i < MEM_SIZE)
		a.mem[i] = i % 256;
	ft_memset(a.mem_info, 0, MEM_SIZE * sizeof(t_mem_info));
	i = -1;
	a.mem_info[i + 2].process = 1;
	a.mem_info[i + 2].player_process = 1;
	a.mem_info[i + 4].process = 1;
	a.mem_info[i + 4].player_process = 1;
	a.mem_info[i + 20].process = 1;
	a.mem_info[i + 20].player_process = 2;
	a.mem[i + 20] = 0x01;
	a.mem_info[i + 2].cycle = 10;
	a.mem_info[i + 3].cycle = 10;
	a.mem_info[i + 4].cycle = 10;
	a.mem_info[i + 5].cycle = 10;
	while (++i < MEM_SIZE / 4)
	{
		a.mem_info[i].player = 1;
	}
	i = (MEM_SIZE >> 1) - 1;
	a.mem_info[i - 30].process = 1;
	a.mem_info[i - 30].player_process = 1;
	a.mem_info[i - 60].process = 1;
	a.mem_info[i - 60].player_process = 2;
	a.mem_info[i + 2].process = 1;
	a.mem_info[i + 2].player_process = 2;
	a.mem_info[i + 15].process = 1;
	a.mem_info[i + 15].player_process = 2;
	a.mem_info[i + 40].process = 1;
	a.mem_info[i + 40].player_process = 1;
	a.mem_info[i + 4].cycle = 10;
	a.mem_info[i + 5].cycle = 10;
	a.mem_info[i + 6].cycle = 10;
	a.mem_info[i + 7].cycle = 10;
	while (++i < MEM_SIZE / 4 + (MEM_SIZE >> 1))
	{
		a.mem_info[i].player = 2;
	}
	ft_exec(&a);
//	close(termfd);
	return (0);
}
