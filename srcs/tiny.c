#include "libft.h"
#include "malloc.h"

t_arena_header *find_tiny()
{
	t_arena_header *tiny;

	if ((tiny = match_header(unused_tiny_space)))
		return (tiny);
	else
	{
		tiny = get_new_header();
		return (init_arena_header(tiny, T_TINY));
	}
}

size_t		unused_tiny_space(t_arena_header *header)
{
	uint16_t i;

	if (!(header->type == T_TINY))
		return (0);
	i = 0;
	while (header->arena.tiny.size[i] && i < (g_manager.page_size / TINY))
		i++;
	return (i != g_manager.page_size / TINY ? 1 : 0);
}

void			*set_tiny_alloc(t_arena_header *header, uint8_t size)
{
	uint16_t i;

	i = 0;
	while (header->arena.tiny.size[i] && (i < g_manager.page_size / TINY))
		i++;
	header->arena.tiny.size[i] = size;
	return ((uint8_t*)header->loc + (TINY * i));
}

void			print_tiny_alloc(t_arena_header *header)
{
	uint16_t i;

	if (!(header->type == T_TINY) || !header->used)
		return;
	i = 0;
	ft_putstr("TINY : ");
	print_addr(header->loc);
	ft_putstr("\n");
	while (i < 16)
	{
		if (header->arena.tiny.size[i])
		{
			print_addr((void*)((size_t)header->loc + i * 256));
			ft_putstr(" - ");
			print_addr((void*)((size_t)header->loc + i * 256 + header->arena.tiny.size[i]));
			ft_putstr(" : ");
			ft_putstr(ft_static_ulltoa(header->arena.tiny.size[i]));
			ft_putstr(" octets\n");
		}
		i++;
	}
}
