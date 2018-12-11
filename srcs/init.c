#include "libft.h"
#include "malloc.h"

void	init_manager()
{
	g_manager.page_size = (uint32_t)getpagesize();
	g_manager.headers = new_header_page();
	g_manager.err = 0;
}

t_arena_header	*init_arena_header(t_arena_header *header, uint8_t type)
{
	header->loc = new_arena_page();
	if (!header->loc)
		return (NULL);
	header->type = type;
	ft_bzero(&(header->arena), sizeof(header->arena));
	header->used = 1;
	return (header);
}
