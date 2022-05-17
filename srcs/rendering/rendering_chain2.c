/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_chain2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:31:36 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/16 09:41:36 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include "libft.h"
#include "game.h"



void	destroy_graphics(t_rendering_element *elem)
{
	t_list	*lst;
	t_list	*prev;

	lst = g_rendering_chain;
	prev = NULL;
	if (lst->content == elem)
	{
		g_rendering_chain = lst->next;
		free(elem->element_pos);
		free(elem);
		free(lst);
	}
	while (lst)
	{
		if (lst->content == elem)
		{
			prev->next = lst->next;
			free(elem->element_pos);
			free(elem);
			free(lst);
		}
		prev = lst;
		lst = lst->next;
	}
}

/*
	Ajoute un element a la chaine de render.
*/
t_rendering_element	*add_graphics(t_color (*eval)(t_rendering_data),
			int layer, t_vector2 *pos, t_vector2 size)
{
	t_list				*new_elem;
	t_rendering_element	*element;

	element = mmalloc(sizeof(t_rendering_element));
	element->element_pos = pos;
	element->element_size = size;
	element->layer = layer;
	element->eval = eval;
	new_elem = ft_lstnew(element);
	ft_lstadd_back(&g_rendering_chain, new_elem);
	return (element);
}

void	destroy_element(void *data)
{
	t_rendering_element	*elem;

	elem = (t_rendering_element *)data;
	free(elem->element_pos);
	free(elem);
}

void	free_graphics(void)
{
	ft_lstclear(&g_rendering_chain, &destroy_element);
}
