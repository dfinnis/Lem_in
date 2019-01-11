/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 13:35:57 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/09 18:23:39 by svaskeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/ft_printf/ft_printf.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

#define NAME_SPACE 0

typedef struct		s_lem_in
{
	char			**argv;
	char			*line;
	int				ant_count;
	struct s_room	*room;
	int				start_flag;
	int				end_flag;
	struct s_room	*start;
	struct s_room	*end;
	struct s_link	*link;
}					t_lem_in;

// typedef struct		s_parse
// {
// 	int				line_count;
// 	char			*line;
// 	char			*type;
// 	struct s_parse	*next;
// }

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	struct s_room	*next;
//	link to hashtable/graph which contains all links to other rooms;
}					t_room;

typedef struct 		s_link
{
	char			*from;
	char			*to;
	struct s_link	*next;
}					t_link;

/*
**		lem_in.cgit statu
*/

t_lem_in			*ft_lem_in_initialize(t_lem_in *lem_in);
void				ft_lem_in_usage(void);
int					main(int argc, char **argv);

/*
**		parse.c
*/

void				ft_parse_ants(t_lem_in *lem_in);
void				ft_parse_comment(t_lem_in *lem_in);

void				ft_add_room(t_lem_in *lem_in, t_room **new);
void				ft_parse_room(t_lem_in *lem_in);

void				ft_add_link(t_lem_in *lem_in, t_link **new);
void				ft_parse_link(t_lem_in *lem_in);
void				ft_lem_in_parse(t_lem_in *lem_in);

/*
**		display.c
*/

void				ft_display_ants(t_lem_in *lem_in);
void				ft_display_rooms(t_lem_in *lem_in);
void				ft_display_links(t_lem_in *lem_in);

/*
**		error.c
*/

void				ft_lem_in_error(/*t_lem_in *lem_in*/);


#endif
