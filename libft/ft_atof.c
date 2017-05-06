#include "libft.h"

double	ft_atof(char *str)
{
	double	result;
	int		sign;
	int		i;
	double	place_value;

	result = ft_atoi(str);
	sign = (result < 0 ? -1 : 1);
	if (!(str = ft_strchr(str, '.')))
		return (result);
	str++;
	i = 0;
	place_value = 0.1;
	while (ft_isdigit(str[i]))
	{
		result += (str[i] - '0') * place_value * sign;
		place_value /= 10;
		i++;
	}
	return (result);
}
