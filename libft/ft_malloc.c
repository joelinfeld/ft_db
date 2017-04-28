#include "libft.h"

void	*ft_malloc(size_t bytes)
{
	void	*addr;

	addr = malloc(bytes);
	if (!addr)
		ft_crash();
	return (addr);
}
