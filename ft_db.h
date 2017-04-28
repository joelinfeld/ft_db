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
	double	d;
}				t_data;

//struct that contains metadata of the fields in a table
typedef struct	s_field
{
	char *name;
	char *type;
}				t_field;

//struct of cell that containts a u_data as well as data of the field and data type contained in the cell
typedef struct	s_cell
{
	char		*field;//are these needed?
	char		*type;//are these needed?
	t_data		value;
}				t_cell;

//table that consits of a 2D cell array and a table data struct.
typedef struct		s_table
{
	char 		*name;
	int			col_count;
	int			row_count;
	t_field		*fields;
	t_cell		**rows;
}					t_table;

void	ft_serialize_table(t_table tab);
void	ft_serialize_table_data(FILE *fp, t_table tab);
void	ft_serialize_rows(FILE *fp, t_table tab);
t_cell	**ft_deserialize_rows(FILE *fp, t_table tab);
t_table ft_deserialize_table_data(FILE *fp);
t_table	ft_deserialize_table(char *table_name);
void	ft_create_table(void);
void	ft_insert_into(void);
void	ft_select(void);

#endif
