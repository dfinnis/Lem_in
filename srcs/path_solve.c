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

int			ft_count(t_group *group, int ant_c, int depth)
{
	int		sum;
	int		i;
	t_group *paths;

	i = 0;
	sum = ant_c;
	paths = group;
	while (i++ < depth)
	{
		sum += paths->path->length - 2;
		paths = paths->next;
	}
	return (sum);
}

static void	ft_store_shortest(t_lem_in *lem_in, t_groups *tmp, int steps, int i)
{
	lem_in->shortest = tmp;
	lem_in->length = steps;
	lem_in->depth = i;
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
			steps = ft_count(path, lem_in->ant_c, i) / i;
			if (steps < lem_in->length)
				ft_store_shortest(lem_in, tmp, steps, i);
			i++;
		}
		tmp = tmp->next;
	}
}

void		ft_solve_algo(t_lem_in *lem_in)
{
	int		i;

	i = 0;
	while (lem_in->start->links[i])
	{
		if (lem_in->start->links[i] == lem_in->end)
			ft_add_direct_path(lem_in);
		i++;
	}
	while (ft_bfs(lem_in))
		ft_bfs_loop(lem_in);
	ft_reset_flow(lem_in);
	while (ft_bfs_withflow(lem_in))
		ft_bfs_loop(lem_in);
	if (!lem_in->paths)
		ft_lem_in_error(lem_in, "no path");
	else
	{
		ft_remove_duplicates(lem_in);
		ft_group_paths(lem_in);
	}
}
