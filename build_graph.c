#include "lem_in.h"

static void	ft_linkjoin(t_room *room, t_link *link)
{
	int		i;
	t_room	**new_links;

	i = 0;
	while (room->links[i])
		i++;
	if (!(new_links = (t_room **)malloc(sizeof(t_room *) * (i + 2))))
		ft_lem_in_error("ERROR");
	i = 0;
	while (room->links[i])
		new_links[i] = room_links[i++];
	new_links[i++] = link;
	new_links[i] = NULL;
	if (room->links)
		free(room->links);
	room->links = new_links;
}

static void	ft_add_link(t_room *room, t_link *link)
{
	if (room->links)
		ft_linkjoin(room, link);
	else
	{
		if (!(room->links = (t_room **)malloc(sizeof(t_room *) * 2)))
			ft_lem_in_error("ERROR");
		*room->links = link;
		*(room->links + 1) = NULL;
	}
}

void		ft_build_graph(t_lem_in *lem_in)
{
	t_link	*link;
	t_room	*room;

	link = lem_in->link;
	room = lem_in->room;
	while (room)
	{
		while (link)
		{
			if (link->from == room)
				ft_add_link(room, link);
			if (link->to == room)
				ft_add_link(room, link);
			link = link->next;
		}
		room = room->next;
	}
}
