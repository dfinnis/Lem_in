/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_select.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaskeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 18:30:43 by svaskeli          #+#    #+#             */
/*   Updated: 2019/01/16 19:33:55 by svaskeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_compare(t_path *path, t_path *moving)
{
	t_path_room	*highway;
	t_path_room	*moving_high;

	highway = path->highway;
	moving_high = moving->highway;
	while(highway && moving_high)
	{
		if (highway->room != moving_high->room)
			return (0);
		highway = highway->next;
		moving_high = moving_high->next;
	}
	if (!highway && !moving_high)
		return (1);
	else
		return (0);
}

void	ft_remove_path(t_lem_in *lem_in, t_path *path)
{
	t_path		*to_remove;
	t_path_room	*tmp;

	to_remove = lem_in->paths;
	while (to_remove && to_remove->next != path)
		to_remove = to_remove->next;
	to_remove->next = to_remove->next->next;
	to_remove = to_remove->next;
	while (to_remove && to_remove->highway)
	{
		tmp = to_remove->highway;
		to_remove->highway = to_remove->highway->next;
		free(tmp);
	}
//	free(to_remove);
//	to_remove = NULL;
}

void	ft_remove_dublicates(t_lem_in *lem_in)
{
	t_path	*path;
	t_path	*moving_path;

	path = lem_in->paths;
	while (path && path->next)
	{
		moving_path = path->next;
		while (moving_path)
		{
			if (ft_compare(path, moving_path))
			{
				ft_remove_path(lem_in, moving_path);
				moving_path = path->next;
			}
			moving_path = moving_path->next;
		}
		path = path->next;
	}
}
