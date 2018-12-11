# include "libft.h"
# include "malloc.h"

void	clean_header_page(t_arena_header *header)
{
	t_page_header	*page;
	t_page_header	*prev;

	page = (void*)((size_t)header - (size_t)header % g_manager.page_size);
	if (page != g_manager.headers && !is_page_used(page))
	{
		prev = g_manager.headers;
		while (prev->next != page)
			prev = prev->next;
		prev->next = page->next;
		if (page->next)
			((t_page_header*)page->next)->prev = prev;
		munmap(page, g_manager.page_size);
	}
}

size_t	is_page_used(void *page)
{
	t_arena_header	*header;

	header = (void*)((size_t)page + sizeof(t_page_header));
	while ((size_t)header <= (size_t)page + (g_manager.page_size - sizeof(t_arena_header)))
	{
		if (header->used)
			return (1);
		header++;
	}
	return (0);
}
