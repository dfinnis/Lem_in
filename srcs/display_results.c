/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_results.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 16:46:28 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/20 20:16:33 by svaskeli         ###   ########.fr       */
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

static void	ft_populate_array(t_lem_in *lem_in)
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
		tmp = lem_in->shortest->group;
		j = 0;
		while (tmp && j < lem_in->depth && i < lem_in->ant_c)
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

static char	*ft_build_ant(int i, t_ant *ant, t_lem_in *lem_in)
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

static char	*ft_build_line(t_lem_in *lem_in, char *line, int i)
{
	char	*ant;

	if (lem_in->array[i - 1]->path)
	{
		ant = ft_build_ant(i, lem_in->array[i - 1], lem_in);
		if (*line && ant)
		{
			if (!(line = ft_strjoinfree_s1(line, " ")))
				ft_lem_in_error(lem_in, "strjoin space fail");
		}
		if (ant)
			if (!(line = ft_strjoinfree(line, ant)))
				ft_lem_in_error(lem_in, "strjoin ant fail");
	}
	return (line);
}

int			ft_is_end(t_lem_in *lem_in)
{
	int i;

	i = 0;
	while (lem_in->array[i])
	{
		if (!lem_in->array[i]->end)
			return (1);
		i++;
	}
	return (0);
}

void		ft_display_results(t_lem_in *lem_in)
{
	int		i;
	int		j;
	char	*line;

	j = 0;
//	ft_sort_group(lem_in);
	ft_populate_array(lem_in);
	while (ft_is_end(lem_in))
	{
		i = 1;
		j++;
		if (!(line = ft_strdup("")))
			ft_lem_in_error(lem_in, "strdup fail in ft_display_results");
		while (i <= lem_in->ant_c)
		{
			line = ft_build_line(lem_in, line, i++);
			if (i > j * lem_in->depth) //too many ants in one line???
				break ;
		}
		ft_printf("%s\n", line);
		free(line);
		line = NULL;
	}
	lem_in->turn_count = j;
}
