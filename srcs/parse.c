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
			ft_lem_in_error(/*lem_in*/"invalid first line: number of ants");
	if (!(lem_in->ant_count = ft_atoi_intmax(lem_in->line)))//correct atoi??
		ft_lem_in_error(/*lem_in*/"invalid first line: number of ants");
	if (lem_in->ant_count < 1)
		ft_lem_in_error(/*lem_in*/"number of ants out of acceptable range");
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
		ft_lem_in_error(/*lem_in*/"malloc room fail");
	(*new)->name = NULL;
	(*new)->x = 0;
	(*new)->y = 0;
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

void	ft_check_duplicate(t_lem_in *lem_in, t_room	*new)
{
	t_room	*tmp;

	tmp = lem_in->room;
	while (tmp && tmp != new)
	{
		if ((ft_strcmp(tmp->name, new->name) == 0) &&
			(tmp->x == new->x && tmp->y == new->y))
			ft_lem_in_error(/*lem_in, */"duplicate room name and coordinates");
		if (ft_strcmp(tmp->name, new->name) == 0)
			ft_lem_in_error(/*lem_in, */"duplicate room name");
		if (tmp->x == new->x && tmp->y == new->y)
			ft_lem_in_error(/*lem_in, */"duplicate room coordinates");
		tmp = tmp->next;
	}
}

void	ft_parse_room(t_lem_in *lem_in)
{
	int		n;
	t_room	*new;

	n = 0;
	ft_add_room(lem_in, &new);
	// if (NAME_SPACE)
	// {
	while (lem_in->line[n])
		n++;
	n--;
	if (!ft_isdigit(lem_in->line[n]))
		ft_lem_in_error(/*lem_in*/"y coordinate not digit");
	while (lem_in->line[n] && ft_isdigit(lem_in->line[n]))
		n--;
	new->y = ft_atoi(lem_in->line + ++n);
	n -= 2;
	if (!ft_isdigit(lem_in->line[n]))
		ft_lem_in_error(/*lem_in*/"x coordinate not digit");
	while (lem_in->line[n] && ft_isdigit(lem_in->line[n]))
		n--;
	new->x = ft_atoi(lem_in->line + ++n);
	n--;
	if (!(new->name = ft_strndup(lem_in->line, n)))
		ft_lem_in_error(/*lem_in*/"strdup room name fail");
	if (!NAME_SPACE && ft_strchr(new->name, ' '))
		ft_lem_in_error(/*lem_in, */"room formatted incorrectly (want to accept spaces in names? #define NAME_SPACE 1)");
//	}
	// else
	// {
	// 	while (lem_in->line[n] && (lem_in->line[n] != ' '))
	// 		n++;
	// 	if (!(new->name = ft_strndup(lem_in->line, n)))
	// 		ft_lem_in_error(/*lem_in*/"strdup room name fail");
	// 	new->x = ft_atoi(lem_in->line + ++n);//fix over max int bug
	// 	while (lem_in->line[n] && ft_isdigit(lem_in->line[n]))
	// 		n++;
	// 	new->y = ft_atoi(lem_in->line + ++n);//fix over max int bug
	// 	while (lem_in->line[n] && ft_isdigit(lem_in->line[n]))
	// 		n++;
	// 	if (lem_in->line[n])
	// 		ft_lem_in_error(/*lem_in, */"room formatted incorrectly
	// 		(want to accept spaces in names? #define NAME_SPACE 1)");
	// }

	ft_check_duplicate(lem_in, new);
	if (lem_in->start_flag)
	{
		// if (lem_in->start)//already a start;
		// 	ft_lem_in_error(/*lem_in*/);
		lem_in->start = new;
		lem_in->start_flag = 0;
	}
	else if (lem_in->end_flag)
	{
		// if (lem_in->end)//already an end
		// 	ft_lem_in_error(/*lem_in*/);
		lem_in->end = new;
		lem_in->end_flag = 0;
	}
}

void	ft_add_link(t_lem_in *lem_in, t_link **new)
{
	t_link	*tmp;

	if (!((*new) = (t_link *)malloc(sizeof(t_link))))
		ft_lem_in_error(/*lem_in*/"malloc link fail");
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

void	ft_is_room(t_lem_in *lem_in, char *link)
{
	t_room	*tmp;
	int		found;

	found = 0;
	tmp = lem_in->room;
	while (tmp && tmp->next)
	{
		if (ft_strcmp(tmp->name, link) == 0)
		{
			found = 1;
			break;
		}
		tmp = tmp->next;
	}
	if (tmp)
		if (ft_strcmp(tmp->name, link) == 0)
			found = 1;
	if (!found)
		ft_lem_in_error(/*lem_in, */"link to unknown room");
}

void	ft_parse_link(t_lem_in *lem_in)
{
	t_link	*new;
	char	*link;

	ft_add_link(lem_in, &new);
	link = ft_strchr(lem_in->line, '-');
	new->from = ft_strndup(lem_in->line, link - lem_in->line);
	new->to = ft_strdup((link + 1));
	ft_is_room(lem_in, new->from);//check if new->from/to name is a real room
	ft_is_room(lem_in, new->to);
}

void	ft_parse_error(t_lem_in *lem_in)
{
	if (!lem_in->start)
		ft_lem_in_error(/*lem_in*/"no start");
	if (!lem_in->end)
		ft_lem_in_error(/*lem_in*/"no end");
}

void	ft_lem_in_parse(t_lem_in *lem_in)
{
	get_next_line(0, &lem_in->line);
	ft_parse_ants(lem_in);
	ft_freestr(lem_in->line);
	while (get_next_line(0, &lem_in->line) == 1)
	{
		if (lem_in->line[0] == '#')
			ft_parse_comment(lem_in);
		else if (ft_strchr(lem_in->line, '-'))
			ft_parse_link(lem_in);
		else if (ft_strchr(lem_in->line, ' '))
			ft_parse_room(lem_in);
		else
			ft_lem_in_error(/*lem_in*/"line not comment, command, room or link");
		ft_freestr(lem_in->line);
	}
	ft_parse_error(lem_in);
}
