# include "libft.h"
# include "malloc.h"

size_t		contains_ptr(t_arena_header *header, void *p)
{
	size_t	i;

	if (!header->used || header->loc > p)
		return (0);
	i = 0;
	if (header->type == T_TINY)
	{
		while (i < 16)
		{
			if ((size_t)header->loc + i * 256 == (size_t)p)
				return (1);
			i++;
		}
	}
	else if (header->type == T_SMALL)
	{
		while (i < 4)
		{
			if ((size_t)header->loc + header->arena.small.offset[i] == (size_t)p)
				return (1);
			i++;
		}
	}
	else if (header->type == T_LARGE)
		return (p == header->loc);
	return (0);
}


size_t		tiny_index(t_arena_header *header, void *p)
{
	size_t	i;

	i = 0;
	while (i < 16)
	{
		if ((size_t)header->loc + i * 256 == (size_t)p)
			return (i);
		i++;
	}
	return (0);
}

size_t		small_index(t_arena_header *header, void *p)
{
	size_t	i;

	i = 0;
	while (i < 4)
	{
		if ((size_t)header->loc + header->arena.small.offset[i] == (size_t)p)
			return (i);
		i++;
	}
	return (0);
}

void		*new_block(t_arena_header *header, void *p, size_t size)
{
	void	*new;
	size_t	index;

	new = malloc(size);
	if (header->type == T_TINY)
	{
		index = tiny_index(header, p);
		ft_memcpy(new, (void*)((size_t)header->loc + index * 256), header->arena.tiny.size[index]);
	}

	else if (header->type == T_SMALL)
	{
		index = small_index(header, p);
		ft_memcpy(new, (void*)((size_t)header->loc + header->arena.small.offset[index]),
				  header->arena.small.size[index]);
	}
	else
		ft_memcpy(new, header->loc, header->arena.large.size);
	free(p);
	return (new);
}
