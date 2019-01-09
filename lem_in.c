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

#include "lem_in.h"

t_lem_in	*ft_lem_in_initialize(t_lem_in *lem_in)
{
	if(!(lem_in = (t_lem_in *)malloc(sizeof(t_lem_in))))
		ft_lem_in_error(/*lem_in*/);
	lem_in->line = NULL;
}

void	ft_lem_in_usage(void)
{
	ft_putstr("usage:	./lem-in < map.map\n");
	exit(1);
}

void	ft_parse_ants()

void	ft_lem_in_parse(t_lem_in *lem_in);
{
	while (get_next_line(0, &lem_in->line) == 1)
	{
		if ()
			ft_parse_ants(lem_in->line);
		else if ()
			ft_parse_comment(lem_in->line);
		else if ()
			ft_parse_room(lem_in->line);
		else if ()
			ft_parse_link(lem_in->line);
		else
			ft_lem_in_error(/*lem_in*/);
		ft_freestr(lem_in->line);
	}
}

int		main(int argc, char **argv)
{
	char	**str;//
	t_lem_in	lem_in;

	lem_in = NULL;
	str = argv;//
	if (argc == 1)
		ft_lem_in_usage();
	lem_in = ft_lem_in_initialize(lem_in);
//	ft_lem_in_parse();
//	ft_lem_in_solve();
//	ft_lem_in_free(/*struct*/);
	return (0);
}
