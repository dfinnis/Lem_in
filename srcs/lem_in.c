/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 13:40:50 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/13 21:28:09 by svaskeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_lem_in	*ft_lem_in_initialize(t_lem_in *lem_in)
{
	if(!(lem_in = (t_lem_in *)malloc(sizeof(t_lem_in))))
		ft_lem_in_error(/*lem_in*/"malloc lem_in fail");
	lem_in->argv = NULL;
	lem_in->line = NULL;
	lem_in->ant_count = 0;
	lem_in->room = NULL;
	lem_in->start_flag = 0;
	lem_in->end_flag = 0;
	lem_in->start = NULL;
	lem_in->end = NULL;
	lem_in->link = NULL;
	lem_in->paths = NULL;
	lem_in->queue = NULL;
	lem_in->last_queue = NULL;
	return (lem_in);
}

void		ft_lem_in_usage(void)
{
	ft_putstr("usage:	./lem-in < map.map\n");
	exit(1);
}

int			main(int argc, char **argv)
{
	t_lem_in	lem_in;

	if (argc < 0)
		ft_lem_in_usage();
	lem_in = *ft_lem_in_initialize(&lem_in);
	lem_in.argv = argv;//useless
	ft_lem_in_parse(&lem_in);
	ft_display_mirror(&lem_in);
	ft_build_graph(&lem_in);
	ft_ford_fulkerson(&lem_in);//
//	ft_display_ants(&lem_in);
//	ft_display_rooms(&lem_in);
//	ft_display_links(&lem_in);
//	ft_lem_in_solve();
//	ft_lem_in_free(/*lem_in*/);
	return (0);
}
