#ifndef FT_DB_H

#define FT_DB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libft.h"

//union that contains cell data, currently either int or str.
typedef union 	u_data
{
	int 	i;
	char 	*str;
}				t_data;

//struct that contains metadata of the fields in a table
typedef struct	s_field
{
	char *name;
	char *type;
}				t_field;


//table that consits of a 2D cell array and a table data struct.
typedef struct		s_table
{
	char 		*name;
	int			col_cnt;
	int			row_cnt;
	t_field		*flds;
	t_data		***rows;
}					t_table;


//ft_create_table.c
void	ft_create_table(char *buffer);
int		ft_init_tab_flds(t_table *tab, char **args);
int		ft_validate_type(char *type);

//ft_insert_rows.c
void	ft_insert_rows(char *buffer);
int		*ft_get_fld_inds(char **args, int *arg_cnt, t_table tab);
void	ft_populate_new_rows(int *fld_inds, int fld_cnt, t_table *tab);
int		ft_get_insert_cnt(void);
int		ft_wrong_arg_cnt(char **val_args, int fld_cnt, char *buffer);
void	ft_add_row_to_tab(char **val_args, int *fld_inds, t_table *tab);
t_data	**ft_new_row(t_table tab);

//ft_fld.inds.c
int *ft_get_fld_inds(char **fld_args, int *arg_cnt, t_table tab);
int *ft_all_fld_inds(int col_cnt, int *fld_cnt);
int	ft_get_fld_ind(char *fld, t_table tab);
void    *ft_no_fld_match(int *inds, char *fld_name, char *tab_name);

//ft_parse.c
int		ft_parse_function(char *buffer, t_table *tab, char ***args);
char    *ft_get_outer_str(char *buffer);
char    **ft_get_args(char *buffer);
int 	ft_check_str_begin(char *buffer, char *str);

//ft_serialize.c
void	ft_serialize_tab(t_table tab);
void	ft_serialize_tab_data(FILE *fp, t_table tab);
void	ft_serialize_rows(FILE *fp, t_table tab);
void    ft_typrint(char *type, t_data *value, FILE *fp);

//ft_deserialize.c
t_data	***ft_deserialize_rows(int fd, t_table tab);
t_table ft_deserialize_tab_data(int fd);
t_table	ft_deserialize_tab(char *tab_name);
char *ft_get_tab_name(char *name_data);
t_field *ft_get_tab_flds(char *fld_data, int col_cnt);
t_data *ft_get_value(char *type, char *cell_str);

//ft_select.c
void	ft_select(char *buffer);
void	ft_display_rows(int *fld_inds, int fld_cnt, int *row_indss, int row_cnt, t_table tab);

//ft_where.c
int		*ft_get_matches(t_table tab, char **args, int arg_cnt, int *match_cnt);
int		ft_is_match(t_data *row_val, char *type, char *op, char *cmp_val);
int		*ft_where(char *buffer, int *row_cnt, t_table tab);
int		*ft_all_row_inds(int row_cnt, int *match_cnt);


//ft_insert_column.c
void	ft_insert_cols(char *buffer);

//ft_update.c
void	ft_update(char *buffer);

//ft_sort.c
void	ft_sort(char *buffer);

//ft_delete_rows.c
void	ft_delete_rows(char *buffer);

//ft_delete_column.c
void	ft_delete_cols(char *buffer);


#endif
