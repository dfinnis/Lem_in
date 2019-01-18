/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 13:35:57 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/17 11:50:55 by svaskeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/ft_printf/ft_printf.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

#define NAME_SPACE 1
#define LINK_SELF 1
#define LINK_DUP 1

#define BRIGHT		"\x1b[1m"
#define UNDERLINE	"\x1b[4m"
#define GREEN		"\x1B[32m"
#define RED			"\x1B[31m"
#define RESET		"\x1B[0m"

/*
**		main structure - holds pointers to other structures and other information
*/

typedef struct		s_lem_in
{
	char			*line;
	int				ant_count;
	int				start_flag;
	int				end_flag;
	struct s_room	*room;
	struct s_room	*start;
	struct s_room	*end;
	struct s_link	*link;
	struct s_paths	*paths;
	struct s_queue	*queue;
	struct s_queue	*last_queue;
	struct s_groups	*groups;
	struct s_groups	*shortest;
	int				length;
	int				depth;
	struct s_paths	**array;
	int				flag_a;
	int				flag_r;
	int				flag_l;
	int				flag_rl;
	int				flag_p;
	int				flag_g;
	int				flag_all;
}					t_lem_in;

/*
**		a path group - holds pointers to actual paths
*/

typedef struct		s_group
{
	struct s_paths	*path;
	struct s_group	*next;
}					t_group;

/*
**		grouped paths structure - each node has a pointer to a different group
*/

typedef struct			s_groups
{
	struct s_group	*group;
	struct s_group	*last;
	struct s_groups	*next;
	int				size;
	int				total_length;
}					t_groups;

/*
**		a queue data sructure for the BFS algorithm
*/

typedef	struct		s_queue
{
	struct s_room	*room;
	struct s_queue	*next;
}					t_queue;

/*
**		an actual path, each node has a pointer to a room
*/

typedef	struct		s_path
{
	struct s_room	*room;
	struct s_path	*next;
}					t_path;

/*
**		paths structure - holds paths, each node has a pointer to a different path
*/

typedef struct		s_paths
{
	int				length;
	struct s_path	*highway;
	struct s_path	*last;
	struct s_paths	*next;
}					t_paths;

/*
**		rooms with links and full information -> graph structure
*/

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	int				lvl;
	int				flow;
	int				visited;
	struct s_room	*next;
	struct s_room	**links;
}					t_room;

/*
**		to store links, when parsing
*/

typedef struct 		s_link
{
	struct s_room	*from;
	struct s_room	*to;
	struct s_link	*next;
}					t_link;

void    ft_lem_in_solve(t_lem_in *lem_in);

void	ft_display_results(t_lem_in *lem_in);


/*
** 		path_select.c
*/

void				ft_remove_dublicates(t_lem_in *lem_in);
void				ft_group_paths(t_lem_in *lem_in);

/*
** 		find_path.c
*/

int					ft_edmonds_karp(t_lem_in *lem_in);
void				ft_print_paths(t_paths *path);

/*
** 		build_graph.c
*/
void				ft_print_room_links(t_lem_in *lem_in);
void				ft_build_graph(t_lem_in *lem_in);

/*
**		lem_in.c
*/

t_lem_in			*ft_lem_in_initialize(t_lem_in *lem_in);
void				ft_lem_in_usage(void);
void				ft_read_flags(t_lem_in *lem_in, int argc, char **argv);
void				ft_display_bonus(t_lem_in *lem_in);
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
void				ft_display_paths(t_lem_in *lem_in);
void				ft_print_path(t_paths *paths);
void				ft_print_groups(t_lem_in *lem_in);

/*
**		error.c
*/

void				ft_lem_in_error(/*t_lem_in *lem_in, */char *err_message);
void				ft_parse_error(t_lem_in *lem_in);

#endif
