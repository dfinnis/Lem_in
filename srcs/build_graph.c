#include "lem_in.h"

static void	ft_print_room_links_slave(t_lem_in *lem_in, t_room *tmp)
{
	if (tmp == lem_in->start && (ft_strcmp(tmp->links[0]->name, lem_in->end->name) == 0))
		ft_printf("\x1B[32m %24s - \x1B[31m%s\x1B[0m\n", tmp->name, tmp->links[0]->name);
	else if (tmp == lem_in->end && (ft_strcmp(tmp->links[0]->name, lem_in->start->name) == 0))
		ft_printf("\x1B[31m %24s - \x1B[32m%s\x1B[0m\n", tmp->name, tmp->links[0]->name);
	else if (tmp == lem_in->start)
		ft_printf("\x1B[32m %24s\x1B[0m - %s\n", tmp->name, tmp->links[0]->name);
	else if (ft_strcmp(tmp->links[0]->name, lem_in->start->name) == 0)
		ft_printf(" %24s - \x1B[32m%s\x1B[0m\n", tmp->name, tmp->links[0]->name);
	else if (tmp == lem_in->end)
		ft_printf("\x1B[31m %24s\x1B[0m - %s\n", tmp->name, tmp->links[0]->name);
	else if (ft_strcmp(tmp->links[0]->name, lem_in->end->name) == 0)
		ft_printf(" %24s - \x1B[31m%s\x1B[0m\n", tmp->name, tmp->links[0]->name);
	else
		ft_printf(" %24s - %s\n", tmp->name, tmp->links[0]->name);
}

void	ft_print_room_links(t_lem_in *lem_in)
{
	int i;
	t_room	*tmp;

	tmp = lem_in->room;
	ft_printf("\x1b[1mRooms with links:\x1b[0m\n\n");
	ft_printf(" %24s - %-24s\n", "From room", "To rooms");
	ft_printf("----------------------------------------------------\n");
	while (tmp)
	{
		i = -1;
		if (!tmp->links)
		{
			if (tmp == lem_in->start)
				ft_printf(" \x1B[32m%24s\x1B[0m | %s\n", tmp->name, "no links");
			else if (tmp == lem_in->end)
				ft_printf(" \x1B[31m%24s\x1B[0m | %s\n", tmp->name, "no links");
			else
				ft_printf(" %24s | %s\n", tmp->name, "no links");
		}
		if (tmp->links && tmp->links[0])
		{
			ft_print_room_links_slave(lem_in, tmp);
			i++;
		}
		while (tmp->links && tmp->links[++i])
		{
			if (ft_strcmp(tmp->links[i]->name, lem_in->start->name) == 0)
				ft_printf(" %24s - \x1B[32m%s\x1B[0m\n", "", tmp->links[i]->name);
			else if (ft_strcmp(tmp->links[i]->name, lem_in->end->name) == 0)
				ft_printf(" %24s - \x1B[31m%s\x1B[0m\n", "", tmp->links[i]->name);
			else
				ft_printf(" %24s - %s\n", "", tmp->links[i]->name);
		}
		ft_printf("----------------------------------------------------\n");
		tmp = tmp->next;
	}
	ft_printf("\n");
}

static void	ft_linkjoin(t_room *room, t_room *link)
{
	int		i;
	t_room	**new_links;

	i = 0;
	while (room->links[i])
		i++;
	if (!(new_links = (t_room **)malloc(sizeof(t_room *) * (i + 2))))
		ft_lem_in_error(/*lem_in, */"malloc tube fail");
	i = -1;
	while (room->links[++i])
		new_links[i] = room->links[i];
	new_links[i] = link;
	new_links[++i] = NULL;
	if (room->links)
		free(room->links);
	room->links = new_links;
}

static void	ft_add_tubes(t_room *room, t_room *link)
{
	if (room->links)
		ft_linkjoin(room, link);
	else
	{
		if (!(room->links = (t_room **)malloc(sizeof(t_room *) * 2)))
			ft_lem_in_error(/*lem_in, */"malloc first tube fail");
		room->links[0] = link;
		room->links[1] = NULL;
	}
}

void		ft_build_graph(t_lem_in *lem_in)
{
	t_link	*link;
	t_room	*room;

	room = lem_in->room;
	while (room)
	{
		link = lem_in->link;
		while (link)
		{
			if (link->from == room)
			{
				ft_add_tubes(link->to, room);
				ft_add_tubes(room, link->to);
			}
			link = link->next;
		}
//		ft_print_room_links(room);
		room = room->next;
	}
	if (!lem_in->start->links)
		ft_lem_in_error(/*lem_in*/"start has no links");
	if (!lem_in->end->links)
		ft_lem_in_error(/*lem_in*/"end has no links");
}
