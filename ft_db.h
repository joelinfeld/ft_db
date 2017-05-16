/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_db.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 16:34:22 by jinfeld           #+#    #+#             */
/*   Updated: 2017/05/05 20:32:51 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DB_H

# define FT_DB_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "libft.h"

typedef union 	u_data
{
	int 	i;
	float	f;
	char 	*str;
}				t_data;

typedef struct	s_field
{
	char	*name;
	char	*type;
}				t_field;

typedef struct	s_table
{
	char 	*name;
	int		col_cnt;
	int		row_cnt;
	t_field	*flds;
	t_data	***rows;
}				t_table;

/*
**main.c
*/
int     ft_handle_command(char *buffer);

/*
**ft_db_error.c
*/
int		ft_db_error(int code, char *str);

/*
**ft_create_table.c
*/
int		ft_create_table(char *buffer);
int		ft_init_tab_flds(t_table *tab, char **args);
int		ft_validate_type(char *type);
int		ft_repeated_field(char *fld_name, int col_num, t_field *flds);

/*
**ft_delete_cols.c
*/
void	ft_delete_cols(char *buffer);
void	ft_delete_column(int fld_ind, t_table *tab);
int		ft_int_cmp(const void *a, const void *b);

/*
**ft_delete_rows.c
*/
int		ft_delete_rows(char *buffer);

/*
**ft_delete_table.c
*/
int		ft_delete_table(char *buffer);

/*
**ft_deserialize.c
*/
t_data	***ft_deserialize_rows(int fd, t_table tab);
t_table	ft_deserialize_tab_data(int fd);
int		ft_deserialize_tab(char *tab_name, t_table *tab);
char	*ft_get_tab_name(char *name_data);
t_field	*ft_get_tab_flds(char *fld_data, int col_cnt);
t_data	*ft_get_value(char *type, char *cell_str);

/*
**ft_display.c
*/
int     *ft_get_col_widths(int *fld_inds, int fld_cnt,
			int *row_inds, int row_cnt, t_table tab);
void    ft_display_hor_line(int *col_widths, int fld_cnt);
void    ft_display_table_header(int *fld_inds, int fld_cnt,
			int *col_widths, t_table tab);
void    ft_display_rows(int *fld_inds, int fld_cnt,
			int *row_inds, int row_cnt, t_table tab);

/*
**ft_fld_inds.c
*/
int		*ft_get_fld_inds(char **fld_args, int *arg_cnt, t_table tab);
int		*ft_all_fld_inds(int col_cnt, int *fld_cnt);
int		ft_get_fld_ind(char *fld, t_table tab);
void    *ft_no_fld_match(int *inds, char *fld_name);

/*
**ft_free_tab.c
*/
void	ft_free_tab(t_table tab);

/*
**ft_insert_cols.c
*/
int		ft_insert_cols(char *buffer);
int		ft_insert_fld(char *fld_arg, int new_col_cnt, int i, t_table *tab);

/*
**ft_insert_rows.c
*/
void	ft_insert_rows(char *buffer);
void	ft_populate_new_rows(int *fld_inds, int fld_cnt, t_table *tab);
int		ft_get_insert_cnt(void);
int		ft_wrong_arg_cnt(char **val_args, int fld_cnt, char *buffer);
void	ft_add_row_to_tab(char **val_args, int *fld_inds, t_table *tab);
t_data	**ft_new_row(t_table tab);

/*
**ft_order_by.c
*/
int		ft_order_tab(char **args, t_table *tab);
int 	ft_order_by(char *buffer, t_table *tab);

/*
**ft_parse.c
*/
int		ft_parse_function(char *buffer, t_table *tab, char ***args);
char    *ft_get_outer_str(char *buffer);
char    **ft_get_args(char *buffer);
int 	ft_check_str_begin(char *buffer, char *str);

/*
**ft_select.c
*/
int		ft_select(char *buffer);

/*
**ft_serialize.c
*/
void	ft_serialize_tab(t_table tab);
void	ft_serialize_tab_data(FILE *fp, t_table tab);
void	ft_serialize_rows(FILE *fp, t_table tab);
void    ft_typrint(char *type, t_data *value, FILE *fp);

/*
**ft_sort.c
*/
int		ft_sort(char *buffer);
int		ft_row_int_cmp(void *thunk, const void *row1, const void *row2);
int		ft_row_str_cmp(void *thunk, const void *row1, const void *row2);
int		ft_row_flt_cmp(void *thunk, const void *row1, const void *row2);

/*
**ft_update.c
*/
int		ft_update(char *buffer);
void	ft_update_rows(t_table *tab, int *fld_inds,
			int fld_cnt, int *row_inds, int row_cnt);
char	**ft_get_update_vals(int row_ind, int i,
			int row_cnt, int fld_cnt, t_table tab);

/*
**ft_where.c
*/
int		*ft_get_matches(t_table tab, char **args,
			int arg_cnt, int *match_cnt);
int		ft_is_match(t_data *row_val, char *type,
			char *op, char *cmp_val);
int		*ft_where(char *buffer, int *row_cnt, t_table tab);
int		*ft_all_row_inds(int row_cnt, int *match_cnt);

/*
**ft_usage.c
*/
void	ft_usage(void);

#endif
