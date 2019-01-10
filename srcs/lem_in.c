/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 13:40:50 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/09 13:40:52 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_lem_in	*ft_lem_in_initialize(t_lem_in *lem_in)
{
	if(!(lem_in = (t_lem_in *)malloc(sizeof(t_lem_in))))
		ft_lem_in_error(/*lem_in*/);
	lem_in->argv = NULL;
	lem_in->line = NULL;
	lem_in->ant_count = 0;
	lem_in->start = NULL;
	lem_in->end = NULL;
	return (lem_in);
}

void	ft_lem_in_usage(void)
{
	ft_putstr("usage:	./lem-in < map.map\n");
	exit(1);
}

int		main(int argc, char **argv)
{
	t_lem_in	lem_in;

	if (argc == 1)
		ft_lem_in_usage();
	lem_in = *ft_lem_in_initialize(&lem_in);
	lem_in.argv = argv;
//	ft_lem_in_parse();
//	ft_lem_in_solve();
//	ft_lem_in_free(/*struct*/);
	return (0);
}
