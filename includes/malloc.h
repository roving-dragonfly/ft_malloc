/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 02:18:12 by aalves            #+#    #+#             */
/*   Updated: 2019/1/22 15:32:45 by aalvess           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H


# include <stdlib.h>
# include <unistd.h>
# include <sys/mman.h>
# include <pthread.h>
# include "libft.h"

# define TINY 255
# define SMALL 4096

# define T_TINY 1
# define T_SMALL 2
# define T_LARGE 3


# define MMAP_FAILED 1
# define CORRUPTED_HEADER 2

//Page header not freed when empty ?
struct	s_page_header
{
    void	*prev;
	void	*next;
};
typedef	struct s_page_header t_page_header;

//16
struct	s_tiny_arena
{
	uint8_t		size[16];
};

//16
struct	s_small_arena
{
	uint16_t	size[4];
	uint16_t	offset[4];
};

//16
struct	s_large_arena
{
	size_t		size;
	size_t		max_size;
};

//8 ptr. 8 rdm, 16 union
struct	s_arena_header
{
    void		*loc;
	size_t		type : 2;
	size_t		used : 1;
	size_t		padding : 61;
	union Arena
	{
		struct s_tiny_arena tiny;
		struct s_small_arena small;
		struct s_large_arena large;
	} arena;
};
typedef struct s_arena_header	t_arena_header;


struct	s_alloc_manager
{
	t_page_header	*headers;
	uint32_t		page_size;
	uint32_t		err;
};

extern struct s_alloc_manager g_manager;

extern pthread_mutex_t lock;


//Init
void			init_manager(void);
t_arena_header	*init_arena_header(t_arena_header *header, uint8_t type);

//Page
t_page_header	*new_header_page(void);
void			*new_arena_page(void);
void			*match_header(size_t (*f)(t_arena_header* tested));
void			*match_header_var(size_t (*f)(t_arena_header* tested, void *v), void *var);
void			map_headers(void (*f)(t_arena_header* header));

//Arena
t_arena_header	*get_new_header(void);
size_t			unused_header(t_arena_header *header);

//Tiny
t_arena_header	*find_tiny(void);
size_t			unused_tiny_space(t_arena_header *header);
void			*set_tiny_alloc(t_arena_header *header, uint8_t size);
void			print_tiny_alloc(t_arena_header *header);

//Small
t_arena_header	*find_small(uint16_t size);
size_t			unused_small_space(t_arena_header *header, void *size);
uint16_t		available_space_at_index(t_arena_header *header, uint16_t index);
void			*set_small_alloc(t_arena_header *header, uint16_t size);
void			print_small_alloc(t_arena_header *header);

//Large
t_arena_header	*find_large(void);
size_t			unused_large_space(t_arena_header *header);
void			*set_large_alloc(t_arena_header *header, size_t size);
void			print_large_alloc(t_arena_header *header);

//Debug
void			show_tiny_alloc(void);
void			show_alloc_mem(void);
void			print_addr(void *p);
void			show_alloc_by_type(t_arena_header *header, void *type);

//Free
size_t			freed_header(t_arena_header* header,  void *p);
size_t			free_in_tiny(t_arena_header* header, void *p);
size_t			free_in_small(t_arena_header* header, void *p);
size_t			free_in_large(t_arena_header* header, void *p);

//Cleaner
void			clean_header_page(t_arena_header *header);
size_t			is_page_used(void *page);

//Realloc
size_t			contains_ptr(t_arena_header *header, void *p);
void			*new_block(t_arena_header *header, void *p, size_t size);
size_t			tiny_index(t_arena_header *header, void *p);
size_t			small_index(t_arena_header *header, void *p);

//Resize
size_t	   		resize_block(t_arena_header *header, void *p, size_t size);
size_t	   		resize_tiny(t_arena_header *header, void *p, size_t size);
size_t	   		resize_small(t_arena_header *header, void *p, size_t size);
uint16_t		available_space_after_index(t_arena_header *header, uint16_t index);
size_t	   		resize_large(t_arena_header *header, size_t size);

//Main
void			*malloc(size_t size);
void			free(void *p);
void			*realloc(void *p, size_t size);

#endif
