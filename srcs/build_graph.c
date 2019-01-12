#include "lem_in.h"

void	ft_print_room_links(t_room *room)
{
	int i;

	i = -1;
	while (room->links[++i])
		ft_printf("%s\n", room->links[i]->name);
	ft_printf("-------------------------\n");
}

static void	ft_linkjoin(t_room *room, t_room *link)
{
	int		i;
	t_room	**new_links;

	i = 0;
	while (room->links[i])
		i++;
	if (!(new_links = (t_room **)malloc(sizeof(t_room *) * (i + 2))))
		ft_lem_in_error("ERROR");
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
			ft_lem_in_error("ERROR");
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
			if (link->to == room)
			{
				ft_add_tubes(link->from, room);
				ft_add_tubes(room, link->from);
			}
			link = link->next;
		}
//		ft_print_room_links(room);
		room = room->next;
	}
}
