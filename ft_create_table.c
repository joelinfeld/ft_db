#include "ft_db.h"



void	ft_create_table(char *buffer)
{
	t_table	tab;
	char	**args;

	tab.name = ft_get_outer_str(buffer);
	if (!tab.name)
		return ; //free name?
	if (access(tab.name, F_OK) != -1)
	{
		ft_printf("Table \"%s\" Already Exists\n", tab.name);
		return ;
	}
	args = ft_get_args(buffer);
	if (!args)
		return ;
	if (ft_init_tab_flds(&tab, args) < 0)
		return ; //free name and args?
	//ft_arrdel2(args);
	tab.row_cnt = 0;

	ft_serialize_tab(tab);
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
		{
			ft_printf("Format Error\n");
			return (-1);//free fields and splits
		}
		if (!ft_validate_type(split[1]))
			return (-1);//free fields and splits
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
	if (valid == 0)
		ft_printf("Type Unsupported\n");
	return (valid);
}



