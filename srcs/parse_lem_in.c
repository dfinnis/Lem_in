/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lem_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 17:09:47 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/09 17:09:48 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_parse_ants(t_lem_in *lem_in);
{
	
}//all final error handling

void	ft_parse_comment(t_lem_in *lem_in);
{
	if (ft_strcmp(lem_in->line, "##start") == 0)

	else if (ft_strcmp(lem_in->line, "##end") == 0)

	else
}

void	ft_parse_room(t_lem_in *lem_in);
{
	
}

void	ft_parse_link(t_lem_in *lem_in);
{
	
}

void	ft_lem_in_parse(t_lem_in *lem_in);
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
