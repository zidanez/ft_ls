/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_l.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 12:32:36 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/08/11 13:37:07 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_len	*get_max_lens(t_len *l1, t_len *l2)
{
	l1->link = l1->link < l2->link ? l2->link : l1->link;
	l1->size = l1->size < l2->size ? l2->size : l1->size;
	l1->blck = l1->blck < l2->blck ? l2->blck : l1->blck;
	l1->user = l1->user < l2->user ? l2->user : l1->user;
	l1->grou = l1->grou < l2->grou ? l2->grou : l1->grou;
	return (l1);
}

static t_len	*get_lens(t_file *f)
{
	t_len	*l;

	if (!(l = (t_len*)malloc(sizeof(t_len))))
		exit(0);
	l->link = ft_nbrlen(f->st.st_nlink);
	l->size = ft_nbrlen(f->st.st_size);
	l->blck = ft_nbrlen(f->det->block);
	l->user = ft_strlen(f->det->user);
	l->grou = ft_strlen(f->det->group);
	return (l);
}

void			get_data_l(t_nowdir **ndir, const char all)
{
	t_file			*f;
	t_dlist			*list;

	if (!((*ndir)->l = (t_len*)malloc(sizeof(t_len))))
		exit(0);
	ft_bzero((*ndir)->l, sizeof(t_len));
	list = (*ndir)->file;
	while (list)
	{
		f = (t_file *)list->content;
		list = list->next;
		if (!all && f->name[0] == '.')
			continue;
		f->det = get_data_file(f->f_path, f->st);
		f->det->l = get_lens(f);
		(*ndir)->l = get_max_lens((*ndir)->l, f->det->l);
		(*ndir)->total += f->det->block;
	}
}
