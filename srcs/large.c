/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   large.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 09:30:22 by aalves             #+#    #+#            */
/*   Updated: 2019/01/23 07:26:26 by aalves            ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "malloc.h"

t_arena_header	*find_large()
{
	t_arena_header *large;

	if ((large = match_header(unused_large_space)))
		return (large);
	else
		return (large = get_new_header());
}

size_t			unused_large_space(t_arena_header *header)
{
	if (!(header->type == T_LARGE) || header->used)
		return (0);
	return (1);
}

void			*set_large_alloc(t_arena_header *header, size_t size)
{
	void		*alloc;
	uint16_t	n_page;

	n_page = (uint16_t)(size / g_manager.page_size + (size % g_manager.page_size ? 1 : 0));
	alloc = mmap(NULL, g_manager.page_size * n_page , PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (!alloc)
	{
		g_manager.err = MMAP_FAILED;
		return (NULL);
	}
	header->type = T_LARGE;
	header->arena.large.size = size;
	header->arena.large.max_size = n_page * g_manager.page_size;
	header->loc = alloc;
	header->used = 1;
	return (alloc);
}

void			print_large_alloc(t_arena_header *header)
{
	if (!(header->type == T_LARGE) || !header->used)
		return;
	ft_putstr("LARGE : ");
	print_addr(header->loc);
	ft_putstr("\n");
	print_addr(header->loc);
	ft_putstr(" - ");
	print_addr((void*)((size_t)header->loc + header->arena.large.size));
	ft_putstr(" : ");
	ft_putstr(ft_static_ulltoa(header->arena.large.size));
	ft_putstr(" octets\n");
}
