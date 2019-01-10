/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 11:11:11 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/10 11:11:12 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

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

void	ft_parse_room(t_lem_in *lem_in)
{
	int		n;
	t_room	*room;

	n = 0;
	room = NULL;
	while (lem_in->line[n] && (lem_in->line[n] != ' '))
		n++;
	if (!(room->name = ft_strndup(lem_in->line, n)))
		ft_lem_in_error(lem_in);
	if (lem_in->start_flag)
	{
		// if (lem_in->start)//already a start;
		// 	ft_lem_in_error(lem_in);
		lem_in->start = room;
		lem_in->start_flag = 0;
	}
	else if (lem_in->end_flag)
	{
		// if (lem_in->end)//already an end
		// 	ft_lem_in_error(lem_in);
		lem_in->end = room;
		lem_in->end_flag = 0;
	}
	//store room somehow
}

// void	ft_parse_link(t_lem_in *lem_in)
// {

// }

void	ft_lem_in_parse(t_lem_in *lem_in)
{
	while (get_next_line(0, &lem_in->line) == 1)
	{
		if (lem_in->line[0] == '#')
			ft_parse_comment(lem_in);
		else if (ft_strchr(lem_in->line, ' '))
			ft_parse_room(lem_in);
		// else if (ft_strchr(lem_in->line, '-'))
		// 	ft_parse_link(lem_in);
		else
			ft_parse_ants(lem_in);
		ft_freestr(lem_in->line);
	}
}
