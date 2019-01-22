/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 13:20:53 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/20 20:37:05 by svaskeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	ft_find_length(t_group *path, int depth, int ants, int size)
{
	t_group	*tmp;
	int		j;
	int		steps;

	tmp = path;
	j = 1;
	steps = tmp->path->length - 2 + (ants / depth);
	while (tmp && j <= depth && j <= size)
	{
		if (steps <= tmp->path->length - 2 + (ants / depth))
			steps = tmp->path->length - 2 + (ants / depth);
		tmp = tmp->next;
		j++;
	}
	return (steps);
}

static void	ft_store_shortest(t_lem_in *lem_in, t_groups *tmp, int steps, int i)
{
	lem_in->shortest = tmp;
	lem_in->length = steps;
	lem_in->depth = i;
	lem_in->org_depth = i;
}

void		ft_lem_in_solve(t_lem_in *lem_in)
{
	t_group		*path;
	t_groups	*tmp;
	int			i;
	int			steps;

	lem_in->shortest = lem_in->groups;
	lem_in->length = lem_in->shortest->group->path->length - 2 + lem_in->ant_c;
	lem_in->depth = 1;
	if (lem_in->ant_c == 1)
		return ;
	tmp = lem_in->groups;
	while (tmp)
	{
		i = 1;
		path = tmp->group;
		while (i <= lem_in->ant_c && i <= tmp->size)
		{
			steps = ft_find_length(path, i, lem_in->ant_c, tmp->size);
			if (steps <= lem_in->length)
				ft_store_shortest(lem_in, tmp, steps, i);
			i++;
		}
		tmp = tmp->next;
	}
}
