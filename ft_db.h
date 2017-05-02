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
	int			col_count;
	int			row_count;
	t_field		*fields;
	t_data		***rows;
}					t_table;


//ft_create_table.c
void	ft_create_table(char *buffer);
int		ft_init_table_fields(t_table *tab, char **args);
int		ft_validate_type(char *type);

//ft_insert_into.c
void	ft_insert_into(char *buffer);

//ft_parse.c
char    *ft_get_outer_str(char *buffer);
char    **ft_get_args(char *buffer);
int 	ft_check_str_begin(char *buffer, char *str);

//ft_serialize.c
void	ft_serialize_table(t_table tab);
void	ft_serialize_table_data(FILE *fp, t_table tab);
void	ft_serialize_rows(FILE *fp, t_table tab);

//ft_deserialize.c
t_data	***ft_deserialize_rows(FILE *fp, t_table tab);
t_table ft_deserialize_table_data(FILE *fp);
t_table	ft_deserialize_table(char *table_name);



#endif
