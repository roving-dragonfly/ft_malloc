#include "libft.h"
#include "malloc.h"

size_t			freed_header(t_arena_header* header,  void *p)
{
	if (!header->used || header->loc > p)
		return (0);
	if (header->type == T_TINY)
		return (free_in_tiny(header, p));
	else if (header->type == T_SMALL)
		return (free_in_small(header, p));
	else if (header->type == T_LARGE)
		return (free_in_large(header, p));
	return (0);
}

size_t	free_in_tiny(t_arena_header* header, void *p)
{
	size_t i;

	if ((size_t)p > (size_t)header->loc + g_manager.page_size)
		return (0);
	i = 0;
	while (i < 16)
	{
		if (header->arena.tiny.size[i] && (size_t)p == (size_t)header->loc + i * 256)
		{
			header->arena.tiny.size[i] = 0;
			i = 0;
			while (i < 16)
			{
				if (header->arena.tiny.size[i])
					return (1);
				i++;
			}
			header->used = 0;
			return (1);
		}
		i++;
	}
	return (0);
}

size_t	free_in_small(t_arena_header* header, void *p)
{
	size_t i;

	if ((size_t)p > (size_t)header->loc + g_manager.page_size)
		return (0);
	i = 0;
	while (i < 4)
	{
		if (header->arena.small.size[i] && (size_t)p ==
			(size_t)header->loc + header->arena.small.offset[i])
		{
			header->arena.small.size[i] = 0;
			header->arena.small.offset[i] = 0;
			ft_putstr("freed small\n");
			i = 0;
			while (i < 4)
			{
				if (header->arena.small.size[i])
					return (1);
				i++;
			}
			header->used = 0;
			return (1);
		}
		i++;
	}
	return (0);
}

size_t	free_in_large(t_arena_header* header, void *p)
{
	if (p != header->loc)
		return (0);
	header->used = 0;
	munmap(header->loc, header->arena.large.size);
	ft_putstr("freed large\n");
	return (1);
}
