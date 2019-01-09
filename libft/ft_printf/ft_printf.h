/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 15:06:08 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/06 15:04:27 by svaskeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft.h"
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct		s_print
{
	unsigned int	printed;
	unsigned int	len;
	char			*form;
	char			type;
	int				hh;
	int				h;
	int				j;
	int				ll;
	int				l;
	int				up_l;
	int				z;
	int				hash;
	int				zero;
	int				minus;
	int				plus;
	int				space;
	int				width;
	int				prec;
	int				prec_set;
	int				sign;
	int				hex_o_zero;
	int				num_zero;
	int				char_zero;
	int				print_negative;
	int				print_plus;
	int				wild_width;
	int				wild_prec;
}					t_print;

/*
**		ft_printf.c
*/
void				ft_parse(t_print *all, va_list ap);
void				ft_read(t_print *all, va_list ap);
void				ft_justify(char *num_str, t_print *all);
void				ft_print(char *num_str, t_print *all);
int					ft_printf(char const *format, ...);

/*
**		initialize.c
*/
void				ft_initialize_print(t_print *all);
void				ft_reinitialize(t_print *all);

/*
**		parse_flags_width.c
*/
int					ft_isflag(char c);
void				ft_parse_flags(t_print *all);
void				ft_wild_width(t_print *all, va_list ap);
void				ft_parse_width(t_print *all, va_list ap);

/*
**		parse_precision.c
*/
void				ft_wild_prec(t_print *all, va_list ap);
void				ft_read_prec(t_print *all, unsigned int n);
void				ft_parse_precision(t_print *all, va_list ap);

/*
**		parse_length.c
*/
int					ft_islength(char c);
void				ft_hh(t_print *all);
void				ft_ll(t_print *all);
void				ft_parse_length(t_print *all);

/*
**		parse_type.c
*/
int					ft_istype(char c);
void				ft_parse_type(t_print *all);
void				ft_parse_upcase(t_print *all);
void				ft_update_conflicts(t_print *all);

/*
**		read_numbers.c
*/
void				ft_int(t_print *all, va_list ap);
void				ft_unsigned(t_print *all, va_list ap);
void				ft_int_octal(t_print *all, va_list ap);
void				ft_int_hex(t_print *all, va_list ap);
void				ft_number(t_print *all, va_list ap);

/*
**		read_floats.c
*/
void				ft_double(t_print *all, va_list ap);
void				ft_float(t_print *all, va_list ap);
void				ft_long_double(t_print *all, va_list ap);
void				ft_float_type(t_print *all, va_list ap);

/*
**		read_others.c
*/
intmax_t			ft_int_len(t_print *all, va_list ap);
uintmax_t			ft_unsigned_len(t_print *all, va_list ap);
void				ft_string(t_print *all, va_list ap);
void				ft_char(t_print *all, va_list ap);
void				ft_pointer(t_print *all, va_list ap);

/*
**		build_precision.c
*/
char				*ft_prec_a(char *num_str, t_print *all, int i);
char				*ft_prec_b(char *num_str, t_print *all, int i);
char				*ft_prec_c(char *num_str, t_print *all, int i);
char				*ft_precision(char *num_str, t_print *all);

/*
**		build_width.c
*/
int					ft_is_unsigned(t_print *all);
int					ft_is_unsigned_wo(t_print *all);
void				ft_calc_width(t_print *all);
char				*ft_build_width(t_print *all, char c);
char				*ft_fill_width(char *num_str, t_print *all, char c);

/*
**		build_prefix.c
*/
char				*ft_negative(char *num_str, t_print *all);
int					ft_0x_condition(t_print *all);
int					ft_o_condition(t_print *all);
char				*ft_build_prefix(char *num_str, t_print *all);

/*
**		build_float.c
*/
char				*ft_9_float(char *num_str, t_print *all, int i, int len);
char				*ft_0_float(char *num_str, t_print *all, int l, int len);
char				*ft_precision_float(char *num_str, t_print *all);
char				*ft_itoa_double(long double n, t_print *all);
char				*ft_itoa_float(long double n, t_print *all);

/*
**		error_protection.c
*/
void				ft_error(char *s1, char *s2);
char				*ft_strdup_empty(char *form);
char				*ft_strjoinfree_error(char *s1, char *s2, char *form);
char				*ft_strjoinfree_s1_error(char *s1, char *s2, char *form);
char				*ft_strjoinfree_s2_error(char *s1, char *s2, char *form);

/*
**		binary.c
*/
void				ft_binary(t_print *all, va_list ap);

#endif
