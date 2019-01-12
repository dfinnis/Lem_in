/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 11:11:11 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/12 17:57:47 by svaskeli         ###   ########.fr       */
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
	if (!(lem_in->ant_count = ft_atoi(lem_in->line)))//correct atoi??
		ft_lem_in_error(/*lem_in*/"invalid first line: number of ants");
	if (lem_in->ant_count < 1)
		ft_lem_in_error(/*lem_in*/"number of ants out of acceptable range");
}

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
	t_room	*new;

	n = 0;
	ft_add_room(lem_in, &new);
	while (lem_in->line[n])
		n++;
	if (!ft_isdigit(lem_in->line[--n]))
		ft_lem_in_error(/*lem_in*/"y coordinate not digit");
	while (lem_in->line[n] && ft_isdigit(lem_in->line[n]))
		n--;
	new->y = ft_atoi(lem_in->line + n + 1);
	if (!ft_isdigit(lem_in->line[--n]))
		ft_lem_in_error(/*lem_in*/"x coordinate not digit");
	while (lem_in->line[n] && ft_isdigit(lem_in->line[n]))
		n--;
	new->x = ft_atoi(lem_in->line + n + 1);
	if (!(new->name = ft_strndup(lem_in->line, n)))
		ft_lem_in_error(/*lem_in*/"strdup room name fail");
	if (new->name[0] == 'L')
		ft_lem_in_error(/*lem_in, */"room name starts with 'L'");
	if (!NAME_SPACE && ft_strchr(new->name, ' '))
		ft_lem_in_error(/*lem_in, */"room formatted incorrectly (want to accept spaces in names? #define NAME_SPACE 1)");
	ft_check_duplicate(lem_in, new);
	ft_start_end(lem_in, new);
}

t_room	*ft_find_room(t_lem_in *lem_in, char to_from)
{
	t_room	*tmp;
	int		i;

	i = 0;
	tmp = lem_in->room;
	while (lem_in->line[i] != '-')
		i++;
	while (tmp && to_from == 'f')
	{
		if (ft_strncmp(tmp->name, lem_in->line, (size_t)i) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	while (tmp && to_from == 't')
	{
		if (ft_strcmp(tmp->name, &(lem_in->line[i + 1])) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_parse_link(t_lem_in *lem_in)
{
	t_link	*new;
//	char	*link;

	ft_add_link(lem_in, &new);
//	link = ft_strchr(lem_in->line, '-');
//	new->from = ft_strndup(lem_in->line, link - lem_in->line);
	if (!(new->from = ft_find_room(lem_in, 'f')))
		ft_lem_in_error("link to unknown room");
	if (!(new->to = ft_find_room(lem_in, 't')))
		ft_lem_in_error("link to unknown room");
//	new->to = ft_strdup((link + 1));
//	ft_is_room(lem_in, new->from);//check if new->from/to name is a real room
//	ft_is_room(lem_in, new->to);
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
		else if (ft_strchr(lem_in->line, ' '))
			ft_parse_room(lem_in);
		else if (ft_strchr(lem_in->line, '-')) //add links into seperate get_next_line
			ft_parse_link(lem_in);
		else
			ft_lem_in_error(/*lem_in*/"line not comment, command, room or link");
		ft_freestr(lem_in->line);
	}
	ft_parse_error(lem_in);
}
