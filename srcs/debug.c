# include "libft.h"
# include "malloc.h"

void	show_alloc_mem()
{
	map_headers(print_tiny_alloc);
	map_headers(print_small_alloc);
	map_headers(print_large_alloc);
}

void	print_addr(void *p)
{
	ft_putstr("Ox");
	ft_putstr(ft_static_ulltoa_base((size_t)p, "0123456789ABCDEF"));
}
