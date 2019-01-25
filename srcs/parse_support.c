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

t_room	*ft_find_room(t_lem_in *lem_in, char to_from)
{
	t_room	*tmp;
	int		i;

	i = 0;
	tmp = lem_in->room;
	while (lem_in->line[i] != '-')
		i++;
	while (tmp && to_from == 'f')
	{
		if (ft_strncmp(tmp->name, lem_in->line, (size_t)i) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	while (tmp && to_from == 't')
	{
		if (ft_strcmp(tmp->name, &(lem_in->line[i + 1])) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
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
			break ;
		}
		tmp = tmp->next;
	}
	if (!found)
		ft_lem_in_error(lem_in, "link to unknown room");
}

void	ft_room_error(t_lem_in *lem_in, t_room *new)
{
	if (new->name[0] == 'L')
		ft_lem_in_error(lem_in, "room name starts with 'L'");
	if (!NAME_SPACE && ft_strchr(new->name, ' '))
		ft_lem_in_error(lem_in, "room name contains space");
	ft_check_duplicate(lem_in, new);
}
