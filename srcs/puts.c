/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 13:37:08 by fnancy            #+#    #+#             */
/*   Updated: 2019/08/11 14:58:38 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			put_l(const t_format f, t_nowdir *dir)
{
	t_dlist		*list;
	t_file		*file;

	get_data_l(&dir, f.all);
	list = dir->file;
	if (!f.dir)
		ft_printf("total %d\n", dir->total);
	while (list)
	{
		file = (t_file *)list->content;
		list = list->next;
		if ((!f.all && (file->name[0] == '.')) || file->det->rights[0] == '<')
			continue ;
		formatter(file, f, dir->l);
	}
}

void			put_one(const t_format f, t_nowdir *dir)
{
	t_dlist		*list;
	t_file		*file;

	list = dir->file;
	if (f.siz && ((!f.all && dir->c_files > 2) || f.all) && !f.dir)
		ft_printf("total %d\n", dir->total);
	while (list)
	{
		file = (t_file*)list->content;
		list = list->next;
		if (!f.all && file->name[0] == '.')
			continue ;
		if (f.siz)
		{
			ft_putchar_n(' ', dir->m_blck_size - file->blck_size);
			ft_printf("%d ", file->st.st_blocks);
		}
		ft_printf("%s\n", file->name);
	}
}
