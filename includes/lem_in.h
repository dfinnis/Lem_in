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

typedef struct		s_lem_in
{
	char			*line;
	int				ant_count;
	struct s_room	*start;
	struct s_room	*end;
}					t_lem_in;

typedef struct	s_room
{
	char	*name;
//	int		x;
//	int		y;
}				t_room;

#endif
