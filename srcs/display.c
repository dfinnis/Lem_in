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
	ft_printf("Number of ants:\n%d\n\n", lem_in->ant_count);
}

void	ft_display_rooms(t_lem_in *lem_in)
{
	t_room	*tmp;

	tmp = lem_in->room;
	ft_printf("Rooms:\n");
	while (tmp)
	{
		if (tmp == lem_in->start)
			ft_printf("Start: %s\n", tmp->name);
		else if (tmp == lem_in->end)
			ft_printf("End: %s\n", tmp->name);
		else
			ft_printf("%s\n", tmp->name);
		tmp = tmp->next;
	}
	ft_printf("\n");
}

void	ft_display_links(t_lem_in *lem_in)
{
	t_link	*tmp;

	tmp = lem_in->link;
	ft_printf("Links:\n");
	while (tmp)
	{
		ft_printf("%s-%s\n", tmp->from, tmp->to);
		tmp = tmp->next;
	}
	ft_printf("\n");
}
