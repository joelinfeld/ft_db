#include "ft_db.h"

int		ft_create_table(char *buffer)
{
	t_table	tab;
	char	**args;

	if(!(tab.name = ft_get_outer_str(buffer)))
		return (ft_db_error(2, ""));  //free name?
	if (access(tab.name, F_OK) != -1)
		return (ft_db_error(1, tab.name));
	args = ft_get_args(buffer);
	if (!args)
		return(ft_db_error(2, ""));
	if (ft_init_tab_flds(&tab, args) > 0)
		return (0); //free name and args?
	//ft_arrdel2(args);
	tab.row_cnt = 0;
	ft_serialize_tab(tab);
	return (0);
}

int		ft_init_tab_flds(t_table *tab, char **args)
{
	char	**split;
	int		i;

	tab->col_cnt = ft_arrlen2(args);
	tab->flds = (t_field*)ft_malloc(sizeof(t_field) * tab->col_cnt);
	i = -1;
	while (++i < tab->col_cnt)
	{
		split = ft_strsplit(args[i], ' ');	
		if (ft_arrlen2(split) != 2)
			return(ft_db_error(2, ""));
		if (!ft_validate_type(split[1]))
			return (ft_db_error(3, split[1]));//free fields and splits
		tab->flds[i].name = ft_strdup(split[0]);
		tab->flds[i].type = ft_strdup(split[1]);
		//ft_arrdel2(split);
	}
	return (0);
}

int		ft_validate_type(char *type)
{
	int		valid;

	valid = 0;
	ft_str_tolower(&type);
	if (ft_strequ(type, "int"))
		valid = 1;
	else if (ft_strequ(type, "str"))
		valid = 1;
	return (valid);
}
