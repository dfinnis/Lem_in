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

static int	ft_reset_path(t_lem_in *lem_in, int i, t_group *tmp, int depth)
{
	int	steps;
	int	dp;
	int	ret;

	dp = 1;
	ret = 0;
	steps = ft_find_length(tmp, lem_in->depth, lem_in->ant_c - i, depth);
	while (dp < lem_in->depth)
	{
		if (steps > ft_find_length(tmp, dp, lem_in->ant_c - i, depth))
		{
			steps = ft_find_length(tmp, dp, lem_in->ant_c - i, depth);
			ret = dp;
		}
		dp++;
	}
	return (ret);
}

void		ft_populate_array(t_lem_in *lem_in)
{
	t_ant	**array;
	int		i;
	int		j;
	t_group	*tmp;

	i = 0;
	if (!(array = (t_ant **)malloc(sizeof(t_ant *) * (lem_in->ant_c + 1))))
		ft_lem_in_error(lem_in, "malloc fail in ft_populate_array");
	while (i < lem_in->ant_c)
	{
		j = 1;
		tmp = lem_in->shortest->group;
		if (ft_reset_path(lem_in, i + 1, tmp, lem_in->depth))
			lem_in->depth = ft_reset_path(lem_in, i + 1, tmp, lem_in->depth);
		while (tmp && j++ <= lem_in->depth && i < lem_in->ant_c)
		{
			ft_initialize_ant(&array[i], lem_in);
			array[i++]->path = tmp->path->highway;
			tmp = tmp->next;
			if (j == 2 && i != 1)
				array[i - 1]->last = 1;
		}
	}
	array[i] = NULL;
	lem_in->array = array;
}
