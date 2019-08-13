/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 15:42:43 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/08/11 13:36:20 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		compare_tim(void *one, void *two)
{
	if (((t_file *)one)->st.st_mtimespec.tv_sec < \
		((t_file *)two)->st.st_mtimespec.tv_sec)
		return (-1);
	return (1);
}

static int		compare_name(void *one, void *two)
{
	return (ft_strcmp(((t_file *)one)->name, ((t_file *)two)->name));
}

static void		ft_dlst_rev(t_dlist **list)
{
	t_dlist		*current;
	t_dlist		*next;
	t_dlist		*prev;
	t_dlist		*nach;

	current = (*list);
	while (current->next != NULL)
		current = current->next;
	nach = current;
	current = nach->prev;
	nach->next = current;
	nach->prev = NULL;
	prev = nach;
	while (current)
	{
		next = current->prev;
		current->prev = prev;
		current->next = next;
		prev = current;
		current = current->next;
	}
	(*list) = nach;
}

void			sort(t_dlist **list, const t_format f)
{
	if (f.nsr)
		return ;
	if (f.tim)
		ft_dlst_rgnsort(list, compare_tim);
	else
		ft_dlst_gnsort(list, compare_name);
	if (f.rev)
		ft_dlst_rev(list);
}
