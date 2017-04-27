#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//union that contains cell data, currently either int or str.
typedef union 	u_data
{
	int i;
	char str[100];
}				t_data;

//struct of cell that containts a u_data as well as metadata of the field and data type contained in the cell
typedef struct	s_cell
{
	char		*field_name;
	char		*type;
	t_data		value;//union?
}				t_cell;

//table_data struct contains all table meta data
typedef struct	s_table_data
{
	char		*name;
	int			col_count;
	int			row_count;
	t_cell		*fields;
}				t_table_data;

//table that consits of a 2D cell array and a table data struct.
typedef struct		s_table
{
	t_table_data 	table_data;
	t_cell			rows[2][2];
}					t_table;

//this serializes a table data struct, creates the first line of a serialized file
void		ft_serialize_table_data(t_table_data td)//need to include row_count
{
	FILE	*fp;
	int i;

	fp = fopen(td.name, "w");
	fprintf(fp, "%lu:\"%s\",", strlen(td.name), td.name);
	fprintf(fp, "%d,{", td.col_count);
	i = 0;
	while (i < td.col_count)
	{
		fprintf(fp, "%lu:\"%s\",", strlen(td.fields[i].field_name), td.fields[i].field_name);
		fprintf(fp, "%s;", td.fields[i].type);
		i++;
	}
	fprintf(fp, "},");
	fprintf(fp, "%d\n", td.row_count);
	fclose(fp);
}

//this function will be used to determine which print based on data type contained in cells
void		typrint(char *type, t_data value, FILE *fp)
{
	if (*type == 'i')
		fprintf(fp, "%d,", value.i);
	else if (*type == 's')
		fprintf(fp, "%lu:\"%s\",", strlen(value.str), value.str);
}

//this serializes all rows contained in a table, should never be called before ft_serialize_table_data
void		ft_serialize_rows(t_table tab)
{
	FILE	*fp;
	int		i;
	int		k;

	fp = fopen(tab.table_data.name, "a");
	i = 0;
	while (i < tab.table_data.row_count)
	{
		k = 0;
		while (k < tab.table_data.col_count)
		{
			typrint(tab.rows[i][k].type, tab.rows[i][k].value, fp);
			k++;
		}
		fprintf(fp, "\n");
		i++;
	}
	fclose(fp);
}

/*
**these functions allow for user input to create a new table, crating rows not yet functional.
int		ft_create_table(void)
{
	FILE	*fp;
	char	name[100];
	int		field_count;
	char 	info[100];
	int 	i;

	printf("TABLE NAME: ");
	scanf("%s", name);
	fp = fopen(name, "w");
	fprintf(fp, "%lu:\"%s\",", strlen(name), name);
	printf("# OF FIELDS: ");
	scanf("%d", &field_count);
	fprintf(fp, "%d,{", field_count);
	i = 0;
	while(i++ < field_count)
	{
		printf("FIELD: ");
		scanf("%s", info);
		fprintf(fp, "%lu:\"%s\",", strlen(info), info);
		printf("TYPE (i/d/s): ");
		scanf("%s", info);
		fprintf(fp, "%s;", info);
	}
	fprintf(fp, "}");
	fclose(fp);
	return (0);
}

int		ft_insert_into(void)
{
	char table_name[100];
	FILE *fp;

	printf("TABLE: ");
	scanf("%s", table_name);
	if (acces(table_name, F_OK) != -1)
	{
		fp = fopen(file_name, "r+");
		//fscanf gets
		lseek(fp, 0, SEEK_END);


	}
	else
		printf("Table Does Not Exist\n");


int		ft_handle_command(char *command)
{
	if (!strcmp(command, "CREATE TABLE"))
		ft_create_table();
	else if (!strcmp(command, "INSERT INTO"))
		ft_insert_into();

	return (0);
}
*/

int main(void)
{
/*	
	char command[100];

	while (1)
	{
		printf("COMMAND: ");
		scanf("%s", command);
		ft_handle_command(command);
	}
*/

//this is all haphazard code to rig together one table with two rows for testing serialization algorithm
	t_table_data td;
	
	td.name = (char*)malloc(5);
	strcpy(td.name, "test");
	td.col_count = 2;
	td.row_count = 2;

	td.fields = (t_cell*)malloc(sizeof(t_cell) * 2);

	td.fields[0].field_name = (char *)malloc(10);
	td.fields[0].type = (char *)malloc(2);

	strcpy(td.fields[0].field_name, "id");

	strcpy(td.fields[0].type, "i");


	td.fields[1].field_name = (char *)malloc(10);
	td.fields[1].type = (char *)malloc(2);

	strcpy(td.fields[1].field_name, "name");
	strcpy(td.fields[1].type, "s");

	ft_serialize_table_data(td);

	t_table tab;
	tab.table_data = td;
	tab.rows[0][0].value.i = 2;
	tab.rows[0][0].type = (char*)malloc(2);
	strcpy(tab.rows[0][0].type, "i");
	tab.rows[0][1].type = (char*)malloc(2);
	strcpy(tab.rows[0][1].type, "s");
	strcpy(tab.rows[0][1].value.str, "bj");
	tab.rows[1][0].value.i = 2;
	tab.rows[1][0].type = (char*)malloc(2);
	strcpy(tab.rows[1][0].type, "i");
	tab.rows[1][1].type = (char*)malloc(2);
	strcpy(tab.rows[1][1].type, "s");
	strcpy(tab.rows[1][1].value.str, "bj");

	ft_serialize_rows(tab);

	return (0);
}
