/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 12:49:05 by fnancy            #+#    #+#             */
/*   Updated: 2019/08/11 16:32:34 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			free_details(t_detail **det)
{
	if (*det)
	{
		if ((*det)->l)
			free((*det)->l);
	}
	free((*det));
	(*det) = NULL;
}

void			free_file(t_file **file)
{
	if ((*file)->det)
		free_details(&(*file)->det);
	if ((*file)->name)
		free((*file)->name);
	if ((*file)->f_path)
		free((*file)->f_path);
	free((*file));
	(*file) = NULL;
}

void			free_dir(t_nowdir **dir)
{
	t_dlist		*list;
	t_dlist		*now;
	t_file		*file;

	if ((*dir))
	{
		free((*dir)->name);
		if ((*dir)->access == 1)
		{
			list = (*dir)->file;
			while (list)
			{
				now = list->next;
				file = (t_file *)list->content;
				if (file)
					free_file(&file);
				free(list);
				list = now;
			}
			if ((*dir)->l)
				free((*dir)->l);
		}
		free((*dir));
	}
}

void			free_double_dlist(t_dlist ***dlist)
{
	t_dlist	**cp;

	cp = (*dlist);
	free(cp);
}
