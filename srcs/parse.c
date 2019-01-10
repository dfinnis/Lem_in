/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 11:11:11 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/10 14:36:09 by svaskeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_parse_ants(t_lem_in *lem_in)
{
	int	i;

	i = -1;
	while (lem_in->line[++i])
		if (!(ft_isdigit(lem_in->line[i])))
			ft_lem_in_error(/*lem_in*/);
	if (!(lem_in->ant_count = ft_atoi(lem_in->line)))//correct atoi??
		ft_lem_in_error(/*lem_in*/);
}//all final error handling

void	ft_parse_comment(t_lem_in *lem_in)
{
	if (ft_strcmp(lem_in->line, "##start") == 0)
		lem_in->start_flag = 1;
	else if (ft_strcmp(lem_in->line, "##end") == 0)
		lem_in->end_flag = 1;
}

void	ft_add_room(t_lem_in *lem_in, t_room **new)
{
	t_room	*tmp;

	if (!((*new) = (t_room *)malloc(sizeof(t_room))))
		ft_lem_in_error(/*lem_in*/);
	(*new)->name = NULL;
//	new->x = 0;
//	new->y = 0;
	(*new)->next = NULL;
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

void	ft_parse_room(t_lem_in *lem_in)
{
	int		n;
	t_room	*new;

	n = 0;
	ft_add_room(lem_in, &new);
	while (lem_in->line[n] && (lem_in->line[n] != ' '))
		n++;
	if (!(new->name = ft_strndup(lem_in->line, n)))
		ft_lem_in_error(lem_in);
	if (lem_in->start_flag)
	{
		// if (lem_in->start)//already a start;
		// 	ft_lem_in_error(lem_in);
		lem_in->start = new;
		lem_in->start_flag = 0;
	}
	else if (lem_in->end_flag)
	{
		// if (lem_in->end)//already an end
		// 	ft_lem_in_error(lem_in);
		lem_in->end = new;
		lem_in->end_flag = 0;
	}
}

void	ft_add_link(t_lem_in *lem_in, t_link **new)
{
	t_link	*tmp;

	if (!((*new) = (t_link *)malloc(sizeof(t_link))))
		ft_lem_in_error(/*lem_in*/);
	(*new)->from = NULL;
	(*new)->to = NULL;
	(*new)->next = NULL;
	tmp = lem_in->link;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (*new);
	}
	else
		lem_in->link = *new;
}

void	ft_parse_link(t_lem_in *lem_in)
{
	t_link	*new;
	char	*dash;

	ft_add_link(lem_in, &new);
	dash = ft_strchr(lem_in->line, '-');
	new->from = ft_strndup(lem_in->line, dash - lem_in->line);
	new->to = ft_strdup((dash + 1));
}

void	ft_lem_in_parse(t_lem_in *lem_in)
{
	while (get_next_line(0, &lem_in->line) == 1)
	{
		if (lem_in->line[0] == '#')
			ft_parse_comment(lem_in);
		else if (ft_strchr(lem_in->line, ' '))
			ft_parse_room(lem_in);
		else if (ft_strchr(lem_in->line, '-'))
			ft_parse_link(lem_in);
		else
			ft_parse_ants(lem_in);
		ft_freestr(lem_in->line);
	}
}
