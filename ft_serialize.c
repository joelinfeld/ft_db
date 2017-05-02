#include "ft_db.h"

//this serializes a table data struct, creates the first line of a serialized file
void		ft_serialize_table_data(FILE *fp, t_table tab)
{
	int i;

	fprintf(fp, "%lu:\"%s\",", strlen(tab.name), tab.name);
	fprintf(fp, "%d,{", tab.col_count);
	i = 0;
	while (i < tab.col_count)
	{
		fprintf(fp, "%lu:\"%s\"|", strlen(tab.fields[i].name), tab.fields[i].name);
		fprintf(fp, "%s;", tab.fields[i].type);
		i++;
	}
	fprintf(fp, "},");
	fprintf(fp, "%d\n", tab.row_count);
}







//this function will be used to determine which print based on data type contained in cells
void		ft_typrint(char *type, t_data *value, FILE *fp)
{
	if (!value)
		fprintf(fp, "%c,", '~');
	else if (ft_strequ(type, "int"))
		fprintf(fp, "%d,", value->i);
	else if (ft_strequ(type, "str"))
		fprintf(fp, "%lu:\"%s\",", strlen(value->str), value->str);
}



//this serializes all rows contained in a table, should never be called before ft_serialize_table_data
void		ft_serialize_rows(FILE *fp, t_table tab)
{
	int		i;
	int		k;

	i = 0;
	while (i < tab.row_count)
	{
		k = 0;
		while (k < tab.col_count)
		{
			ft_typrint(tab.fields[k].type, tab.rows[i][k], fp);
			k++;
		}
		fprintf(fp, "\n");
		i++;
	}
}



void	ft_serialize_table(t_table tab)
{
	FILE *fp;

	fp = fopen(tab.name, "w");
	ft_serialize_table_data(fp, tab);
	ft_serialize_rows(fp, tab);
	fclose(fp);
}

