/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 20:31:52 by aalves            #+#    #+#             */
/*   Updated: 2018/11/29 20:31:52 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"
# include "malloc.h"

struct s_alloc_manager	g_manager;
pthread_mutex_t			lock;

void	*malloc(size_t size)
{
	void	*area;

	if (!g_manager.page_size)
	{
		init_manager();
		pthread_mutex_init(&lock, NULL);
	}
	if (!size)
		return (NULL);
	pthread_mutex_lock(&lock);
	if (size <= TINY)
		area = set_tiny_alloc(find_tiny(), (uint8_t)size);
	else if (size <= SMALL)
		area = set_small_alloc(find_small((uint16_t)size), (uint16_t)size);
	else
		area = set_large_alloc(find_large(), size);
	if (g_manager.err)
		ft_putstr("ERROR\n");
	pthread_mutex_unlock(&lock);
	return (area);
}

void	free(void *p)
{
	t_arena_header	*freed;

	if (!p)
		return ;
	pthread_mutex_lock(&lock);
	freed = match_header_var(freed_header, p);
	if (!freed)
	{
		ft_putstr("Pointer being freed was not allocated\n");
		ft_putstr("value ");
		print_addr(p);
		ft_putstr("\n");
		return ;
	}
	if (!freed->used)
		clean_header_page(freed);
	pthread_mutex_unlock(&lock);
}

void	*realloc(void *p, size_t size)
{
	t_arena_header	*header;
	void			*mem;

	if (!p)
		return (malloc(size));
	if (!size)
	{
		free(p);
		return (NULL);
	}
	pthread_mutex_lock(&lock);
	header = match_header_var(contains_ptr, p);
	if (!header)
	{
		pthread_mutex_unlock(&lock);
		return (NULL);
	}
	if (resize_block(header, p, size))
	{
		pthread_mutex_unlock(&lock);
		return (p);
	}
	pthread_mutex_unlock(&lock);
	mem = new_block(header, p, size);
	return (mem);
}
