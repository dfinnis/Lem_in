/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_mirror.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:48:27 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/24 17:48:29 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_display_mirror(t_lem_in *lem_in)
{
	t_room	*tmp_room;
	t_link	*tmp_link;

	tmp_room = lem_in->room;
	tmp_link = lem_in->link;
	ft_printf("%d\n", lem_in->ant_c);
	while (tmp_room)
	{
		if (tmp_room == lem_in->start)
			ft_printf("##start\n%s %d %d\n",
				tmp_room->name, tmp_room->x, tmp_room->y);
		else if (tmp_room == lem_in->end)
			ft_printf("##end\n%s %d %d\n",
				tmp_room->name, tmp_room->x, tmp_room->y);
		else
			ft_printf("%s %d %d\n", tmp_room->name, tmp_room->x, tmp_room->y);
		tmp_room = tmp_room->next;
	}
	while (tmp_link)
	{
		ft_printf("%s-%s\n", tmp_link->from->name, tmp_link->to->name);
		tmp_link = tmp_link->next;
	}
	ft_printf("\n");
}
