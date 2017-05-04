#include "libft.h"

void	ft_str_tolower(char **str)
{
	int		i;

	if (!str || !*str)
		return ;
	i = -1;
	while ((*str)[++i])
		(*str)[i] = ft_tolower((*str)[i]);
}
