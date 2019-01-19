/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_support.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 13:59:27 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/17 11:16:52 by svaskeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_add_room(t_lem_in *lem_in, t_room **new)
{
	t_room	*tmp;

	if (!((*new) = (t_room *)malloc(sizeof(t_room))))
		ft_lem_in_error(lem_in, "malloc fail in ft_add_room");
	ft_bzero(*new, sizeof(**new));
	tmp = lem_in->room;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (*new);
	}
	else
		lem_in->room = *new;
}

void	ft_check_duplicate(t_lem_in *lem_in, t_room	*new)
{
	t_room	*tmp;

	tmp = lem_in->room;
	while (tmp && tmp != new)
	{
		if ((ft_strcmp(tmp->name, new->name) == 0) &&
			(tmp->x == new->x && tmp->y == new->y))
			ft_lem_in_error(lem_in, "duplicate room name and coordinates");
		if (ft_strcmp(tmp->name, new->name) == 0)
			ft_lem_in_error(lem_in, "duplicate room name");
		if (tmp->x == new->x && tmp->y == new->y)
			ft_lem_in_error(lem_in, "duplicate room coordinates");
		tmp = tmp->next;
	}
}

void	ft_start_end(t_lem_in *lem_in, t_room *new)
{
	if (lem_in->start_flag)
	{
		if (lem_in->start)
			ft_lem_in_error(lem_in, "more than one start");
		lem_in->start = new;
		lem_in->start_flag = 0;
	}
	if (lem_in->end_flag)
	{
		if (lem_in->end)
			ft_lem_in_error(lem_in, "more than one end");
		lem_in->end = new;
		lem_in->end_flag = 0;
	}
}

void	ft_add_link(t_lem_in *lem_in, t_link **new)
{
	t_link	*tmp;

	if (!((*new) = (t_link *)malloc(sizeof(t_link))))
		ft_lem_in_error(lem_in, "malloc fail in ft_add_link");
	(*new)->from = NULL;
	(*new)->to = NULL;
	(*new)->next = NULL;
	tmp = lem_in->link;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (*new);
	}
	else
		lem_in->link = *new;
}

void	ft_is_room(t_lem_in *lem_in, char *link)
{
	t_room	*tmp;
	int		found;

	found = 0;
	tmp = lem_in->room;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, link) == 0)
		{
			found = 1;
			break;
		}
		tmp = tmp->next;
	}
	if (!found)
		ft_lem_in_error(lem_in, "link to unknown room");
}
