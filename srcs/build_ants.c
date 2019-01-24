/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 12:50:34 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/22 12:50:35 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	ft_initialize_ant(t_ant **array, t_lem_in *lem_in)
{
	if (!(*array = (t_ant *)malloc(sizeof(t_ant))))
		ft_lem_in_error(lem_in, "malloc fail in ft_initialize_ant");
	ft_bzero(*array, sizeof(**array));
	(*array)->traveled = 1;
}

// static int	ft_reset_path(t_lem_in *lem_in, int i, t_group *tmp, int depth)
// {
// 	int	steps;
// 	int	dp;
// 	int	ret;

// 	dp = 1;
// 	ret = 0;
// 	steps = ft_find_length(tmp, lem_in->depth, lem_in->ant_c - i, depth);
// 	while (dp < lem_in->depth)
// 	{
// 		if (steps > ft_find_length(tmp, dp, lem_in->ant_c - i, depth))
// 		{
// 			steps = ft_find_length(tmp, dp, lem_in->ant_c - i, depth);
// 			ret = dp;
// 		}
// 		dp++;
// 	}
// 	return (ret);
// }

int		ft_count_total(t_lem_in *lem_in)
{
	int sum;
	int	i;
	t_group *paths;

	i = 0;
	sum = lem_in->ant_c;
	paths = lem_in->shortest->group;
	while (i++ < lem_in->depth)
	{
		sum += paths->path->length - 2;
		paths = paths->next;
	}
	return (sum);
}

static	void	ft_path_count(t_lem_in *lem_in)
{
	int count;
	int	i;
	int	j;
	t_group *paths;

	i = lem_in->depth;
	count = ft_count_total(lem_in);
	while (i--)
	{
		j = 0;
		paths = lem_in->shortest->group;
		while(j++ < i)
			paths = paths->next;
		paths->times = count / (i + 1) - (paths->path->length - 2);
		// ft_printf("times %i, count %i, i %i, len %i\n", paths->times, count, i + 1, paths->path->length);
		count -= count / (i + 1);
	}
}

void		ft_populate_array(t_lem_in *lem_in)
{
	t_ant	**array;
	int		ants;
	int		deep;
	// int		l;
	// int		i;
	t_group	*tmp;

	ants = 0;
	if (!(array = (t_ant **)malloc(sizeof(t_ant *) * (lem_in->ant_c + 1))))
		ft_lem_in_error(lem_in, "malloc fail in ft_populate_array");
	ft_path_count(lem_in);
	while (ants < lem_in->ant_c)
	{
		deep = 1;
		// l = 0;
		tmp = lem_in->shortest->group;
		// while (tmp && tmp->next && tmp->next->times)
		// {
		// 	tmp = tmp->next;
		// 	l++;
		// }
		// if (ft_reset_path(lem_in, i + 1, tmp, lem_in->depth))
		// 	lem_in->depth = ft_reset_path(lem_in, i + 1, tmp, lem_in->depth);
		while (tmp && deep++ <= lem_in->depth && ants < lem_in->ant_c && tmp->times)
		{
			ft_initialize_ant(&array[ants], lem_in);
			array[ants++]->path = tmp->path->highway;
			tmp->times--;
			// tmp = lem_in->shortest->group;
			// i = l - 1;
			// while (i-- && tmp)
				tmp = tmp->next;
			// l--;
			if (deep == 2 && ants != 1)
				array[ants - 1]->last = 1;
		}
	}
	array[ants] = NULL;
	lem_in->array = array;
}
