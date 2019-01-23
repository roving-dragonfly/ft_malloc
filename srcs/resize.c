/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 20:37:43 by aalves            #+#    #+#             */
/*   Updated: 2019/01/23 07:25:40 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"
# include "malloc.h"

size_t		resize_block(t_arena_header *header, void *p, size_t size)
{
	if (header->type == T_TINY)
		return (resize_tiny(header, p, size));
	else if (header->type == T_SMALL)
		return (resize_small(header, p, size));
	else
		return (resize_large(header, size));
}

size_t		resize_tiny(t_arena_header *header, void *p, size_t size)
{
	size_t i;

	if (size > TINY)
		return (0);
	i = 0;
	while (i < 16 && (size_t)header->loc + i * TINY != (size_t)p)
		i++;
	header->arena.tiny.size[i] = (uint8_t)size;
	return (1);
}

size_t		resize_small(t_arena_header *header, void *p, size_t size)
{
	size_t i;

	if (size > SMALL)
		return (0);
	i = 0;
	while (i < 4 && (size_t)header->loc + header->arena.small.offset[i] != (size_t)p)
		i++;
	if (available_space_after_index(header, (uint16_t)i) >= size)
	{
		header->arena.small.size[i] = (uint16_t)size;
		return (1);
	}
	return (0);
}

uint16_t		available_space_after_index(t_arena_header *header, uint16_t index)
{
	uint16_t	i;

	i = index + 1;
	while (i < 4)
	{
		if (header->arena.small.offset[i])
			return (header->arena.small.offset[i] - header->arena.small.offset[index]);
		i++;
	}

	return ((uint16_t)g_manager.page_size - header->arena.small.offset[index]);
}

size_t		resize_large(t_arena_header *header, size_t size)
{
	if (size <= header->arena.large.max_size)
	{
		header->arena.large.size = size;
		return (1);
	}
	return (0);
}
