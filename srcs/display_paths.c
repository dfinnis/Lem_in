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

static void	ft_print_path(t_paths *paths)
{
	t_path	*path;

	path = paths->highway;
	while (path)
	{
		ft_printf("%s\n", path->room->name);
		path = path->next;
	}
	ft_printf("\n");
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
		ft_printf("NEW GROUP - %i -\n", j++);
		while (group)
		{
			ft_printf("-- path %i --\n", i++);
			ft_print_path(group->path);
			group = group->next;
		}
		groups = groups->next;
	}
}
