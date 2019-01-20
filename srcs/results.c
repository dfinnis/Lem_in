/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   results_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 10:58:59 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/19 15:28:33 by svaskeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_initialize_ant(t_ant **array, t_lem_in *lem_in)
{
	if (!(*array = (t_ant *)malloc(sizeof(t_ant))))
		ft_lem_in_error(lem_in, "malloc fail in ft_initialize_ant");
	ft_bzero(*array, sizeof(**array));
	(*array)->traveled = 1;
}

void    ft_populate_array(t_lem_in *lem_in)
{
	t_ant	**array;
	int		i;
	int		j;
	t_group	*tmp;

	if (!(array = (t_ant **)malloc(sizeof(t_ant *) * (lem_in->ant_count + 1))))
		ft_lem_in_error(lem_in, "malloc fail in ft_populate_array");
	i = 0;

	while (i < lem_in->ant_count)
	{
		tmp = lem_in->shortest->group;
		j = 0;
		while (tmp && j < lem_in->depth && i < lem_in->ant_count)
		{
			ft_initialize_ant(&array[i], lem_in);
			array[i]->path = tmp->path->highway;
			tmp = tmp->next;
			j++;
			i++;
		}
	}
	array[i] = NULL;
	lem_in->array = array;
}

char    *ft_build_ant(int i, t_ant *ant, t_lem_in *lem_in)
{
	char	*line;
	int		count;
	t_path	*tmp;

	count = 0;
	tmp = ant->path;
	if (ant->end)
		return (NULL);
	while (count++ < ant->traveled)
		tmp = tmp->next;
	if (!(line = ft_strjoinfree_s2("L", ft_itoa(i))))
		ft_lem_in_error(lem_in, "strjoin fail in ft_build_ant");
	if (!(line = ft_strjoinfree_s1(line, "-")))
		ft_lem_in_error(lem_in, "strjoin fail in ft_build_ant");
	if (!(line = ft_strjoinfree_s1(line, tmp->room->name)))
		ft_lem_in_error(lem_in, "strjoin fail in ft_build_ant");
	ant->traveled++;
	if (!tmp->next)
		ant->end = 1;
	return (line);
}

void	ft_sort_group(t_lem_in *lem_in)
{
	t_group	*tmp;
	t_paths	*swap;
	int		count;

	count = 0;
	tmp = lem_in->shortest->group;
	while (tmp && tmp->next && count++ < lem_in->depth)
	{
		if (tmp->path->length > tmp->next->path->length)
		{
			swap = tmp->path;
			tmp->path = tmp->next->path;
			tmp->next->path = swap;
			tmp = lem_in->shortest->group;
		}
		tmp = tmp->next;
	}
}

void    ft_display_results(t_lem_in *lem_in)
{
	int  i;
	int  j;
	char *line;
	char *ant;

	j = 0;
	ft_sort_group(lem_in);
	ft_populate_array(lem_in);
	while (!lem_in->array[lem_in->ant_count - 1]->end || !lem_in->array[0]->end)
	{
		i = 1;
		j++;
		if (!(line = ft_strdup("")))
			ft_lem_in_error(lem_in, "strdup fail in ft_display_results");
		while (i <= lem_in->ant_count)
		{
			if (lem_in->array[i - 1]->path)
			{
				ant = ft_build_ant(i, lem_in->array[i - 1], lem_in);
				if (ft_strcmp(line, ""))
				{
				   	if (!(line = ft_strjoinfree_s1(line, " ")))
						ft_lem_in_error(lem_in, "strjoin " " fail in ft_display_results");
				}
				if (ant)
				{
					if (!(line = ft_strjoinfree(line, ant)))
						ft_lem_in_error(lem_in, "strjoin ant fail in ft_display_results");
				}
			}
			i++;
			if (i > j * lem_in->depth)
				break ;
		}
		ft_printf("%s\n", line);
		if (line)
			free (line);
		line = NULL;
	}
	lem_in->turn_count = j;
}
