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

static int	ft_is_end(t_lem_in *lem_in)
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

static void	ft_print_line(char *line)
{
	ft_printf("%s\n", line);
	free(line);
	line = NULL;
}

void		ft_display_results(t_lem_in *lem_in)
{
	int		i;
	int		j;
	char	*line;

	j = 0;
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
			if (lem_in->array[i - 1] && lem_in->array[i - 1]->last
				&& lem_in->array[i - 1]->traveled == 1)
			{
				lem_in->array[i - 1]->last = 0;
				break ;
			}
		}
		ft_print_line(line);
	}
	lem_in->turn_count = j;
}
