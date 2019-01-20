/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 15:52:05 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/20 15:52:07 by dfinnis          ###   ########.fr       */
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

void	ft_check_duplicate(t_lem_in *lem_in, t_room *new)
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

int		ft_find_coordinate(char *line, int n)
{
	while (line[n] && ft_isdigit(line[n]))
		n--;
	if (line[n] == '-')
		n--;
	return (n);
}

void	ft_max_coordinate(t_lem_in *lem_in, int coordinate)
{
	if (MAX_INT && (coordinate > 2147483647 || coordinate < -2147483648))
		ft_lem_in_error(lem_in, "coordinate outside of int range");
}

void	ft_coordinate_isdigit(t_lem_in *lem_in, char line)
{
	if (!ft_isdigit(line))
		ft_lem_in_error(lem_in, "coordinate not digit");
}
