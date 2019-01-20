/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 13:40:50 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/19 15:28:35 by svaskeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		ft_usage(t_lem_in *lem_in)
{
	ft_putstr("usage:\t");
	ft_putstr("./lem-in [-t] [-a] [-r] [-l] [-rl] [-p] [-all] < map.map\n");
	ft_putstr("\n\t[-t] display number of turns\n");
	ft_putstr("\t[-a] display number of ants\n");
	ft_putstr("\t[-r] display rooms\n");
	ft_putstr("\t[-l] display links\n");
	ft_putstr("\t[-rl] display rooms with links\n");
	ft_putstr("\t[-p] display paths\n");
	ft_putstr("\t[-all] display all\n\n");
	ft_lem_in_free(lem_in);
	exit(1);
}

void		ft_read_flags(t_lem_in *lem_in, int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "-t") == 0)
			lem_in->flag_t = 1;
		else if (ft_strcmp(argv[i], "-a") == 0)
			lem_in->flag_a = 1;
		else if (ft_strcmp(argv[i], "-r") == 0)
			lem_in->flag_r = 1;
		else if (ft_strcmp(argv[i], "-l") == 0)
			lem_in->flag_l = 1;
		else if (ft_strcmp(argv[i], "-rl") == 0)
			lem_in->flag_rl = 1;
		else if (ft_strcmp(argv[i], "-p") == 0)
			lem_in->flag_p = 1;
		else if (ft_strcmp(argv[i], "-all") == 0)
			lem_in->flag_all = 1;
		else
			ft_usage(lem_in);
		i++;
	}
}

void		ft_display_bonus(t_lem_in *lem_in)
{
	if (lem_in->flag_all || lem_in->flag_t || lem_in->flag_a || lem_in->flag_r
		|| lem_in->flag_l || lem_in->flag_rl || lem_in->flag_p)
		ft_printf("\n");
	if (lem_in->flag_all)
	{
		lem_in->flag_t = 1;
		lem_in->flag_a = 1;
		lem_in->flag_r = 1;
		lem_in->flag_l = 1;
		lem_in->flag_rl = 1;
		lem_in->flag_p = 1;
	}
	if (lem_in->flag_t)
		ft_display_turn_count(lem_in);
	if (lem_in->flag_a)
		ft_display_ants(lem_in);
	if (lem_in->flag_r)
		ft_display_rooms(lem_in);
	if (lem_in->flag_l)
		ft_display_links(lem_in);
	if (lem_in->flag_rl)
		ft_print_room_links(lem_in);
	if (lem_in->flag_p)
		ft_display_paths(lem_in);
}

int			main(int argc, char **argv)
{
	t_lem_in	lem_in;

	ft_bzero(&lem_in, sizeof(lem_in));
	ft_read_flags(&lem_in, argc, argv);
	ft_lem_in_parse(&lem_in);
	ft_build_graph(&lem_in);
	ft_edmonds_karp(&lem_in);
	ft_lem_in_solve(&lem_in);
	ft_display_results(&lem_in);
	ft_print_groups(&lem_in);//
	ft_display_bonus(&lem_in);
	ft_lem_in_free(&lem_in);
	return (0);
}
