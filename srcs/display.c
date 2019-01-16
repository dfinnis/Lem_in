/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 14:19:07 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/12 17:16:56 by svaskeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_display_ants(t_lem_in *lem_in)
{
	ft_printf("\x1b[1mNumber of ants:\x1b[0m\n\n %d\n\n", lem_in->ant_count);
}

void	ft_display_rooms(t_lem_in *lem_in)
{
	t_room	*tmp;

	tmp = lem_in->room;
	ft_printf("\x1b[1mRooms:\x1b[0m\n\n");
	ft_printf("\x1b[4m%-12s| %-12s| %-10s| %-12s\x1b[0m\n", " X", " Y", "Start/End", "Name");
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
	ft_printf("\x1b[1mLinks:\x1b[0m\n\n");
	ft_printf("\x1b[4m %24s - %-24s\x1b[0m\n", "From room", "To room");
	while (tmp)
	{
		if ((ft_strcmp(tmp->from->name, lem_in->start->name) == 0) && 
				(ft_strcmp(tmp->to->name, lem_in->end->name) == 0))
			ft_printf("\x1B[32m %24s - \x1B[31m%s\x1B[0m\n", tmp->from->name, tmp->to->name);
		else if ((ft_strcmp(tmp->from->name, lem_in->end->name) == 0) && 
				(ft_strcmp(tmp->to->name, lem_in->start->name) == 0))
			ft_printf("\x1B[31m %24s - \x1B[32m%s\x1B[0m\n", tmp->from->name, tmp->to->name);
		else if (ft_strcmp(tmp->from->name, lem_in->start->name) == 0)
			ft_printf("\x1B[32m %24s\x1B[0m - %s\n", tmp->from->name, tmp->to->name);
		else if (ft_strcmp(tmp->to->name, lem_in->start->name) == 0)
			ft_printf(" %24s - \x1B[32m%s\x1B[0m\n", tmp->from->name, tmp->to->name);
		else if (ft_strcmp(tmp->from->name, lem_in->end->name) == 0)
			ft_printf("\x1B[31m %24s\x1B[0m - %s\n", tmp->from->name, tmp->to->name);
		else if (ft_strcmp(tmp->to->name, lem_in->end->name) == 0)
			ft_printf(" %24s - \x1B[31m%s\x1B[0m\n", tmp->from->name, tmp->to->name);
		else
			ft_printf(" %24s - %s\n", tmp->from->name, tmp->to->name);
		tmp = tmp->next;
	}
	ft_printf("\n");
}

void	ft_display_mirror(t_lem_in *lem_in)
{
	t_room	*tmp_room;
	t_link	*tmp_link;

	tmp_room = lem_in->room;
	tmp_link = lem_in->link;
	ft_printf("%d\n", lem_in->ant_count);
	while (tmp_room)
	{
		if (tmp_room == lem_in->start)
			ft_printf("##start\n%s %d %d\n", tmp_room->name, tmp_room->x, tmp_room->y);
		else if (tmp_room == lem_in->end)
			ft_printf("##end\n%s %d %d\n", tmp_room->name, tmp_room->x, tmp_room->y);
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


void	ft_display_paths(t_lem_in *lem_in)
{
	int i;
	t_path *roads;
	char	*str;

	i = 1;
	str = NULL;
	roads = lem_in->paths;
	ft_printf("\x1b[1mPaths:\x1b[0m\n\n", i);
	while (roads)
	{
		ft_printf("\x1b[4mPath %d\x1b[0m\n", i);
		while (roads->highway->next)
			roads->highway = roads->highway->next;
		while (roads->highway)
		{
			if (roads->highway->room == lem_in->start)
				ft_printf("\x1B[32m%s\x1B[0m\n", roads->highway->room->name);
			else if (roads->highway->room == lem_in->end)
				ft_printf("\x1B[31m%s\x1B[0m\n", roads->highway->room->name);
			else
				ft_printf("%s\n", roads->highway->room->name);
			roads->highway = roads->highway->prev;
		}
		ft_printf("\n");
		i++;
		roads = roads->next;
	}
}
