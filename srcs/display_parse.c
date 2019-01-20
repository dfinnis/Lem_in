/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 16:47:38 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/20 16:47:42 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		ft_display_turn_count(t_lem_in *lem_in)
{
	ft_printf(BRIGHT "Number of turns:\n" RESET);
	ft_printf(" %d\n\n", lem_in->turn_count);
}

void		ft_display_ants(t_lem_in *lem_in)
{
	ft_printf(BRIGHT "Number of ants:\n" RESET);
	ft_printf(" %d\n\n", lem_in->ant_c);
}

void		ft_display_rooms(t_lem_in *lem_in)
{
	t_room	*tmp;

	tmp = lem_in->room;
	ft_printf(BRIGHT "Rooms:\n\n" RESET);
	ft_printf(UNDERLINE "%-12s| %-12s| %-10s| %-12s\n" RESET,
		" X", " Y", "Start/End", "Name");
	while (tmp)
	{
		if (tmp == lem_in->start)
			ft_printf(GREEN "%- 12ld| %- 12ld| %-10s| %s\n" RESET,
				tmp->x, tmp->y, "Start", tmp->name);
		else if (tmp == lem_in->end)
			ft_printf(RED "%- 12ld| %- 12ld| %-10s| %s\n" RESET,
				tmp->x, tmp->y, "End", tmp->name);
		else
			ft_printf("%- 12ld| %- 12ld| %-10s| %s\n",
				tmp->x, tmp->y, "", tmp->name);
		tmp = tmp->next;
	}
	ft_printf("\n");
}

static void	ft_display_links_slave(t_lem_in *lem_in, t_link *tmp)
{
	if ((ft_strcmp(tmp->from->name, lem_in->start->name) == 0)
		&& (ft_strcmp(tmp->to->name, lem_in->end->name) == 0))
		ft_printf("\x1B[32m %24s - \x1B[31m%s\x1B[0m\n",
			tmp->from->name, tmp->to->name);
	else if ((ft_strcmp(tmp->from->name, lem_in->end->name) == 0)
		&& (ft_strcmp(tmp->to->name, lem_in->start->name) == 0))
		ft_printf("\x1B[31m %24s - \x1B[32m%s\x1B[0m\n",
			tmp->from->name, tmp->to->name);
	else if (ft_strcmp(tmp->from->name, lem_in->start->name) == 0)
		ft_printf("\x1B[32m %24s\x1B[0m - %s\n",
			tmp->from->name, tmp->to->name);
	else if (ft_strcmp(tmp->to->name, lem_in->start->name) == 0)
		ft_printf(" %24s - \x1B[32m%s\x1B[0m\n",
			tmp->from->name, tmp->to->name);
	else if (ft_strcmp(tmp->from->name, lem_in->end->name) == 0)
		ft_printf("\x1B[31m %24s\x1B[0m - %s\n",
			tmp->from->name, tmp->to->name);
	else if (ft_strcmp(tmp->to->name, lem_in->end->name) == 0)
		ft_printf(" %24s - \x1B[31m%s\x1B[0m\n",
			tmp->from->name, tmp->to->name);
	else
		ft_printf(" %24s - %s\n", tmp->from->name, tmp->to->name);
}

void		ft_display_links(t_lem_in *lem_in)
{
	t_link	*tmp;

	tmp = lem_in->link;
	ft_printf(BRIGHT "Links:\n\n" RESET);
	ft_printf(UNDERLINE " %24s - %-24s\n" RESET, "From room", "To room");
	while (tmp)
	{
		ft_display_links_slave(lem_in, tmp);
		tmp = tmp->next;
	}
	ft_printf("\n");
}
