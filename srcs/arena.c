#include "libft.h"
#include "malloc.h"

size_t			unused_header(t_arena_header *header)
{
	if (header->used)
		return (0);
	return (1);
}

t_arena_header	*get_new_header()
{
	t_arena_header	*header;

	header = match_header(unused_header);
 	if (header)
		return (header);
	else
	{
		new_header_page();
		return (match_header(unused_header));
	}
}
