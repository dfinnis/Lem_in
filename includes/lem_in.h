/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 13:35:57 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/19 15:14:13 by svaskeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/ft_printf/ft_printf.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# define NAME_SPACE 1
# define LINK_SELF 1
# define LINK_DUP 1
# define MAX_INT 0
# define MAX_ANTS 20000

# define BRIGHT		"\x1b[1m"
# define UNDERLINE	"\x1b[4m"
# define GREEN		"\x1B[32m"
# define RED		"\x1B[31m"
# define RESET		"\x1B[0m"

/*
**		main structure - holds pointers to other structures and information
*/
typedef struct		s_lem_in
{
	char			*line;
	int				ant_c;
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
	int				org_depth;
	struct s_ant	**array;
	int				turn_count;
	int				flag_t;
	int				flag_a;
	int				flag_r;
	int				flag_l;
	int				flag_rl;
	int				flag_p;
	int				flag_g;
	int				flag_all;
}					t_lem_in;

/*
**		rooms with links and full information -> graph structure
*/
typedef struct		s_room
{
	char			*name;
	long long		x;
	long long		y;
	int				lvl;
	int				flow;
	int				visited;
	struct s_room	*next;
	struct s_room	**links;
}					t_room;

/*
**		to store links, when parsing
*/
typedef struct		s_link
{
	struct s_room	*from;
	struct s_room	*to;
	struct s_link	*next;
}					t_link;

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
**		paths structure - holds paths, each node has a pointer to another path
*/
typedef struct		s_paths
{
	int				length;
	struct s_path	*highway;
	struct s_path	*last;
	struct s_paths	*next;
}					t_paths;

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
typedef struct		s_groups
{
	struct s_group	*group;
	struct s_group	*last;
	struct s_groups	*next;
	int				size;
}					t_groups;

/*
**		an individual ant - holds it's path, and how far it's travelled
*/
typedef struct		s_ant
{
	struct s_path	*path;
	int				traveled;
	int				last;
	int				end;
}					t_ant;

/*
**		lem_in.c
*/
int					main(int argc, char **argv);

/*
**		parse.c
*/
void				ft_lem_in_parse(t_lem_in *lem_in);

/*
**		parse_room.c
*/
void				ft_add_room(t_lem_in *lem_in, t_room **new);
int					ft_find_coordinate(char *line, int n);
void				ft_max_coordinate(t_lem_in *lem_in, int coordinate);
void				ft_coordinate_isdigit(t_lem_in *lem_in, char line);

/*
**		parse_support.c
*/

void				ft_check_duplicate(t_lem_in *lem_in, t_room *new);
void				ft_start_end(t_lem_in *lem_in, t_room *new);
void				ft_add_link(t_lem_in *lem_in, t_link **new);
void				ft_is_room(t_lem_in *lem_in, char *link);
t_room				*ft_find_room(t_lem_in *lem_in, char to_from);

/*
** 		build_graph.c
*/
void				ft_build_graph(t_lem_in *lem_in);

/*
** 		path_find.c
*/
void				ft_solve_algo(t_lem_in *lem_in);

/*
** 		path_queue.c
*/
void				ft_add_to_queue(t_lem_in *lem_in, t_room *room);
void				ft_pop_queue(t_lem_in *lem_in);
void				ft_reset_visited(t_lem_in *lem_in);
void				ft_sort_group(t_lem_in *lem_in);

/*
** 		path_build.c
*/
void				ft_update_length(t_paths *path);
void				ft_add_direct_path(t_lem_in *lem_in);
void				ft_recover_path(t_lem_in *lem_in);

/*
** 		path_select.c
*/
void				ft_remove_duplicates(t_lem_in *lem_in);

/*
** 		path_group.c
*/
t_groups			*ft_add_group(t_lem_in *lem_in);
t_groups			*ft_add_to_group(t_groups *group,
	t_paths *path, t_lem_in *lem_in);
void				ft_group_paths(t_lem_in *lem_in);

/*
** 		path_sort.c
*/
t_groups			*ft_sort_paths(t_groups *group);
t_groups			*ft_update_size(t_groups *group);

/*
** 		build_ants.c
*/
void				ft_populate_array(t_lem_in *lem_in);

/*
** 		solve.c
*/
void				ft_lem_in_solve(t_lem_in *lem_in);
int					ft_find_length(t_group *path, int depth, int ants,
	int size);

/*
** 		display_results.c
*/
void				ft_display_results(t_lem_in *lem_in);

/*
**		display.c
*/
void				ft_display_turn_count(t_lem_in *lem_in);
void				ft_display_ants(t_lem_in *lem_in);
void				ft_display_rooms(t_lem_in *lem_in);
void				ft_display_links(t_lem_in *lem_in);

/*
**		display_rl.c
*/
void				ft_display_room_links(t_lem_in *lem_in);

/*
**		display_paths.c
*/
void				ft_display_paths(t_lem_in *lem_in);
void				ft_display_groups(t_lem_in *lem_in);

/*
**		error.c
*/
void				ft_lem_in_error(t_lem_in *lem_in, char *err_message);
void				ft_parse_error(t_lem_in *lem_in);

/*
**		free.c
*/
void				ft_lem_in_free(t_lem_in *lem_in);

/*
**		free_more.c
*/
void				ft_free_ants(t_ant **ant);
void				ft_free_queue(t_queue *queue);

#endif
