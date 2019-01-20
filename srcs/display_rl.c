/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_rl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 16:40:34 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/20 16:40:36 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	ft_display_rl_no_link(t_lem_in *lem_in, t_room *tmp)
{
	if (tmp == lem_in->start)
		ft_printf(" \x1B[32m%24s\x1B[0m | %s\n", tmp->name, "no links");
	else if (tmp == lem_in->end)
		ft_printf(" \x1B[31m%24s\x1B[0m | %s\n", tmp->name, "no links");
	else
		ft_printf(" %24s | %s\n", tmp->name, "no links");
}

static void	ft_display_rl(t_lem_in *lem_in, t_room *tmp)
{
	if (tmp == lem_in->start
		&& (ft_strcmp(tmp->links[0]->name, lem_in->end->name) == 0))
		ft_printf("\x1B[32m %24s - \x1B[31m%s\x1B[0m\n",
			tmp->name, tmp->links[0]->name);
	else if (tmp == lem_in->end
		&& (ft_strcmp(tmp->links[0]->name, lem_in->start->name) == 0))
		ft_printf("\x1B[31m %24s - \x1B[32m%s\x1B[0m\n",
			tmp->name, tmp->links[0]->name);
	else if (tmp == lem_in->start)
		ft_printf("\x1B[32m %24s\x1B[0m - %s\n",
			tmp->name, tmp->links[0]->name);
	else if (ft_strcmp(tmp->links[0]->name, lem_in->start->name) == 0)
		ft_printf(" %24s - \x1B[32m%s\x1B[0m\n",
			tmp->name, tmp->links[0]->name);
	else if (tmp == lem_in->end)
		ft_printf("\x1B[31m %24s\x1B[0m - %s\n",
			tmp->name, tmp->links[0]->name);
	else if (ft_strcmp(tmp->links[0]->name, lem_in->end->name) == 0)
		ft_printf(" %24s - \x1B[31m%s\x1B[0m\n",
			tmp->name, tmp->links[0]->name);
	else
		ft_printf(" %24s - %s\n", tmp->name, tmp->links[0]->name);
}

static void	ft_display_rl_only_link(t_lem_in *lem_in, t_room *tmp, int i)
{
	if (ft_strcmp(tmp->links[i]->name, lem_in->start->name) == 0)
		ft_printf(" %24s - \x1B[32m%s\x1B[0m\n", "", tmp->links[i]->name);
	else if (ft_strcmp(tmp->links[i]->name, lem_in->end->name) == 0)
		ft_printf(" %24s - \x1B[31m%s\x1B[0m\n", "", tmp->links[i]->name);
	else
		ft_printf(" %24s - %s\n", "", tmp->links[i]->name);
}

void		ft_print_room_links(t_lem_in *lem_in)
{
	int		i;
	t_room	*tmp;

	tmp = lem_in->room;
	ft_printf("\x1b[1mRooms with links:\x1b[0m\n\n");
	ft_printf(" %24s - %-24s\n", "From room", "To rooms");
	ft_printf("----------------------------------------------------\n");
	while (tmp)
	{
		i = -1;
		if (!tmp->links)
			ft_display_rl_no_link(lem_in, tmp);
		if (tmp->links && tmp->links[0])
		{
			ft_display_rl(lem_in, tmp);
			i++;
		}
		while (tmp->links && tmp->links[++i])
			ft_display_rl_only_link(lem_in, tmp, i);
		ft_printf("----------------------------------------------------\n");
		tmp = tmp->next;
	}
	ft_printf("\n");
}
