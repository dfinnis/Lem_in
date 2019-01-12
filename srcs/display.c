/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 14:19:07 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/10 14:19:08 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_display_ants(t_lem_in *lem_in)
{
	ft_printf("Number of ants:\n %d\n\n", lem_in->ant_count);
}

void	ft_display_rooms(t_lem_in *lem_in)
{
	t_room	*tmp;

	tmp = lem_in->room;
	ft_printf("Rooms:\n");
	ft_printf("%-12s| %-12s| %-10s| %s\n", " X", " Y", "Start/End", "Name");
	while (tmp)
	{
		if (tmp == lem_in->start)
			ft_printf("\x1B[32m%- 12d| %- 12d| %-10s| %s\x1B[0m\n", tmp->x, tmp->y, "Start", tmp->name);
		else if (tmp == lem_in->end)
			ft_printf("\x1B[31m%- 12d| %- 12d| %-10s| %s\x1B[0m\n", tmp->x, tmp->y, "End", tmp->name);
		else
			ft_printf("%- 12d| %- 12d| %-10s| %s\n", tmp->x, tmp->y, "", tmp->name);
		tmp = tmp->next;
	}
	ft_printf("\n");
}

void	ft_display_links(t_lem_in *lem_in)
{
	t_link	*tmp;

	tmp = lem_in->link;
	ft_printf("Links:\n");
	ft_printf(" %-25s| %s\n", "From room", "To room");
	while (tmp)
	{
		ft_printf(" %-25s| %s\n", tmp->from, tmp->to);
		tmp = tmp->next;
	}
	ft_printf("\n");
}
