/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 16:42:31 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/20 16:42:32 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		ft_display_paths(t_lem_in *lem_in)
{
	int		i;
	t_paths *roads;
	t_path	*highway;

	i = 1;
	roads = lem_in->paths;
	ft_printf(BRIGHT "Paths:\n\n" RESET);
	while (roads)
	{
		ft_printf(UNDERLINE "Path %d\n" RESET, i);
		highway = roads->highway;
		while (highway)
		{
			if (highway->room == lem_in->start)
				ft_printf(GREEN "%s\n" RESET, highway->room->name);
			else if (highway->room == lem_in->end)
				ft_printf(RED "%s\n" RESET, highway->room->name);
			else
				ft_printf("%s\n", highway->room->name);
			highway = highway->next;
		}
		ft_printf("length = %i\n\n", roads->length);
		i++;
		roads = roads->next;
	}
}

static void	ft_print_path(t_lem_in *lem_in, t_paths *paths)
{
	t_path	*path;

	path = paths->highway;
	while (path)
	{
		if (path->room == lem_in->start)
			ft_printf(GREEN "%s\n" RESET, path->room->name);
		else if (path->room == lem_in->end)
			ft_printf(RED "%s\n" RESET, path->room->name);
		else
			ft_printf("%s\n", path->room->name);
		path = path->next;
	}
	ft_printf("\n");
}

void		ft_display_shortest(t_lem_in *lem_in)
{
	t_groups	*groups;
	t_group		*group;
	int			i;
	
	i = 1;
	groups = lem_in->shortest;
	ft_printf(BRIGHT "The chosen group:\n\n" RESET);
	group = groups->group;
	while (group)
	{
		ft_printf("-- path %i --\n", i++);
		ft_print_path(lem_in, group->path);
		group = group->next;
	}
	ft_printf("depth - %i\n", lem_in->org_depth);
}

void		ft_display_groups(t_lem_in *lem_in)
{
	t_groups	*groups;
	t_group		*group;
	int			i;
	int			j;

	groups = lem_in->groups;
	j = 1;
	ft_printf(BRIGHT "Groups:\n\n" RESET);
	while (groups)
	{
		i = 1;
		group = groups->group;
		ft_printf(UNDERLINE "--- Group %i ---\n" RESET, j++);
		while (group)
		{
			ft_printf("-- path %i --\n", i++);
			ft_print_path(lem_in, group->path);
			group = group->next;
		}
		groups = groups->next;
	}
	ft_display_shortest(lem_in);
}
