/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:57:19 by aalves             #+#    #+#            */
/*   Updated: 2019/01/23 07:26:07 by aalves            ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "malloc.h"

t_page_header	*new_header_page()
{
	t_page_header	*page;
	t_page_header	*prev;

	page = mmap(NULL, g_manager.page_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (!page)
	{
		g_manager.err = MMAP_FAILED;
		return (NULL);
	}
	ft_bzero(page, g_manager.page_size);
	prev = g_manager.headers;
	while (prev && prev->next)
		prev = prev->next;
	if (prev)
	{
		page->prev = prev;
		prev->next = page;
	}
	return (page);
}

void			*new_arena_page()
{
	void	*arena;

	arena = mmap(NULL, g_manager.page_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (!arena)
	{
		g_manager.err = MMAP_FAILED;
		return (NULL);
	}
	return (arena);
}

void			*match_header(size_t (*f)(t_arena_header* tested))
{
	uint8_t			*page;
	t_arena_header	*header;

	page = (uint8_t*)g_manager.headers;
	header = (void*)(page + sizeof(t_page_header));
	while (42)
	{
		if ((uint8_t*)header >= page + (g_manager.page_size - sizeof(t_arena_header)))
		{
			if (((t_page_header*)(void*)page)->next)
			{
				page = (uint8_t*)(((t_page_header*)(void*)page)->next);
				header = (void*)(page + sizeof(t_page_header));
				continue;
			}
			else
				return (NULL);
		}
		if (f(header))
			return ((void*)header);
		header++;
	}
}

void			*match_header_var(size_t (*f)(t_arena_header* tested, void *v), void *var)
{
	uint8_t			*page;
	t_arena_header	*header;

	page = (uint8_t*)g_manager.headers;
	header = (void*)(page + sizeof(t_page_header));
	while (42)
	{
		if ((uint8_t*)header >= page + (g_manager.page_size - sizeof(t_arena_header)))
		{
			if (((t_page_header*)(void*)page)->next)
			{
				page = (uint8_t*)(((t_page_header*)(void*)page)->next);
				header = (void*)(page + sizeof(t_page_header));
				continue;
			}
			else
				return (NULL);
		}
		if (f(header, var))
			return ((void*)header);
		header++;
	}
}

void			map_headers(void (*f)(t_arena_header* header))
{
	uint8_t			*page;
	t_arena_header	*header;

	page = (uint8_t*)g_manager.headers;
	header = (void*)(page + sizeof(t_page_header));
	while (42)
	{
		if ((uint8_t*)header >= page + (g_manager.page_size - sizeof(t_arena_header)))
		{
			if (((t_page_header*)(void*)page)->next)
			{
				page = (uint8_t*)(((t_page_header*)(void*)page)->next);
				header = (void*)(page + sizeof(t_page_header));
				continue;
			}
			else
				return;
		}
		f(header);
		header++;
	}
}
