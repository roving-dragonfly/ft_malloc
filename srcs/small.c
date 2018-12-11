#include "libft.h"
#include "malloc.h"

t_arena_header	*find_small(uint16_t size)
{
	t_arena_header *small;

	if ((small = match_header_var(unused_small_space, &size)))
		return (small);
	else
	{
		small = get_new_header();
		return (init_arena_header(small, T_SMALL));
	}
}

size_t			unused_small_space(t_arena_header *header, void *size)
{
	uint16_t	i;

	if (!(header->type == T_SMALL))
		return (0);
	i = 0;
	while (i < 4)
	{
		if (!header->arena.small.size[i] &&
			*(uint16_t*)size <= available_space_at_index(header, i))
			return (1);
		i++;
	}
	return (0);
}


uint16_t		available_space_at_index(t_arena_header *header, uint16_t index)
{
	uint16_t	i;
	uint16_t	j;

	i = index + 1;
	j = index ? index - 1 : 0;
	while (j > 0 && !header->arena.small.size[j])
		j--;
	while (i < 4)
	{
		if (header->arena.small.offset[i])
			return (header->arena.small.offset[i] -
					(header->arena.small.offset[j] + header->arena.small.size[j]));
		i++;
	}
	return ((uint16_t)g_manager.page_size -
			(header->arena.small.offset[j] + header->arena.small.size[j]));
}

void			*set_small_alloc(t_arena_header *header, uint16_t size)
{
	uint16_t	i;
	uint16_t	total;

	i = 0;
	total = 0;
	while (header->arena.small.size[i] || size > available_space_at_index(header, i))
	{
		total += header->arena.small.size[i];
		i++;
	}
	header->arena.small.size[i] = size;
	header->arena.small.offset[i] = total;
	header->used = 1;
	return ((uint8_t*)header->loc + header->arena.small.offset[i]);
}

void			print_small_alloc(t_arena_header *header)
{
	uint16_t i;

	if (!(header->type == T_SMALL) || !header->used)
		return;
	i = 0;
	ft_putstr("SMALL : ");
	print_addr(header->loc);
	ft_putstr("\n");
	while (i < 4)
	{
		if (header->arena.small.size[i])
		{
			print_addr((void*)((size_t)header->loc + header->arena.small.offset[i]));
			ft_putstr(" - ");
			print_addr((void*)((size_t)header->loc + header->arena.small.offset[i] + header->arena.small.size[i]));
			ft_putstr(" : ");
			ft_putstr(ft_static_ulltoa(header->arena.small.size[i]));
			ft_putstr(" octets\n");
		}
		i++;
	}
}
