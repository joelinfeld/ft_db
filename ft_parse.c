#include "ft_db.h"

char	*ft_get_outer_str(char *buffer)
{
	char	*bracket_pnt;
	char	*outer_str;

	bracket_pnt = ft_strchr(buffer, '(');
	if (!bracket_pnt)
	{
		ft_printf("Missing \"(\"\n");
		return (NULL);
	}
	bracket_pnt[0] = '\0';
	outer_str = ft_strtrim(buffer);
	if (!*outer_str || ft_strchr(outer_str, ' ') || ft_strchr(outer_str, '\t'))
	{
		ft_printf("Format Error\n");
		//free(outer_str);
		return (NULL);
	}
	bracket_pnt[0] = '(';
	return (outer_str);
}




char	**ft_get_args(char *buffer)
{
	char	*arg_str;
	char	**split_args;
	char	*bracket_pnt;
	char	*trimmed;
	int		i;

	arg_str = ft_strchr(buffer, '(') + 1;
	bracket_pnt = ft_strchr(arg_str, ')');
	if (!bracket_pnt)
	{
		ft_printf("Format Error\n");
		return (NULL);
	}
	bracket_pnt[0] = '\0';
	split_args = ft_strsplit(arg_str, ',');
	i = -1;
	while (split_args[++i])
	{
		trimmed = ft_strtrim(split_args[i]);
		free(split_args[i]);
		split_args[i] = trimmed;
	}
	return (split_args);
}




int	ft_check_str_begin(char *buffer, char *str)
{
	if (ft_strnequ(buffer, str, ft_strlen(str)))
		return (1);
	else
		return (0);
}

