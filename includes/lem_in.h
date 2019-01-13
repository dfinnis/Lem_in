/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 13:35:57 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/13 21:27:52 by svaskeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/ft_printf/ft_printf.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

#define NAME_SPACE 1

typedef struct		s_lem_in
{
	char			**argv;//
	char			*line;
	int				ant_count;
	int				start_flag;
	int				end_flag;
	struct s_room	*room;
	struct s_room	*start;
	struct s_room	*end;
	struct s_link	*link;
	struct s_path	*paths;
	struct s_queue	*queue;
	struct s_queue	*last_queue;
}					t_lem_in;

// typedef struct		s_parse
// {
// 	int				line_count;
// 	char			*line;
// 	char			*type;
// 	struct s_parse	*next;
// }

/*typedef struct		s_hash
{
	struct s_rooms	*room;
	struct s_hash	*next;
}					t_hash*/

typedef	struct		s_queue
{
	struct s_room	*room;
	struct s_queue	*next;
}					t_queue;

typedef struct		s_path
{
	int				length;
	struct s_room	**path;
	struct s_path	*next;
}					t_path;

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	int				flow;
	int				residual;
	int				visited;
	struct s_room	*next;
	struct s_room	**links;
}					t_room;
	
typedef struct 		s_link
{
	struct s_room	*from;
	struct s_room	*to;
	struct s_link	*next;
}					t_link;

/*
** 		find_path.c
*/

int					ft_ford_fulkerson(t_lem_in *lem_in);

/*
** 		build_graph.c
*/

void				ft_build_graph(t_lem_in *lem_in);

/*
**		lem_in.c
*/

t_lem_in			*ft_lem_in_initialize(t_lem_in *lem_in);
void				ft_lem_in_usage(void);
int					main(int argc, char **argv);

/*
**		parse.c
*/

void				ft_parse_ants(t_lem_in *lem_in);
void				ft_parse_comment(t_lem_in *lem_in);
void				ft_parse_room(t_lem_in *lem_in);
void				ft_parse_link(t_lem_in *lem_in);
void				ft_lem_in_parse(t_lem_in *lem_in);

/*
**		parse_support.c
*/

void				ft_add_room(t_lem_in *lem_in, t_room **new);
void				ft_check_duplicate(t_lem_in *lem_in, t_room	*new);
void				ft_start_end(t_lem_in *lem_in, t_room *new);
void				ft_add_link(t_lem_in *lem_in, t_link **new);
void				ft_is_room(t_lem_in *lem_in, char *link);

/*
**		display.c
*/

void				ft_display_ants(t_lem_in *lem_in);
void				ft_display_rooms(t_lem_in *lem_in);
void				ft_display_links(t_lem_in *lem_in);
void				ft_display_mirror(t_lem_in *lem_in);

/*
**		error.c
*/

void				ft_lem_in_error(/*t_lem_in *lem_in, */char *err_message);
void				ft_parse_error(t_lem_in *lem_in);

#endif
