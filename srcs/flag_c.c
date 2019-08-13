/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 11:07:43 by fnancy            #+#    #+#             */
/*   Updated: 2019/08/11 17:38:21 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static	void		put_1str_mcol(t_nowdir *dir, t_dlist **files, t_mcol *mcol,\
					t_format f)
{
	int		fl;
	int		i;
	t_file	*file;

	fl = 0;
	i = -1;
	if (f.siz && ((!f.all && dir->c_files > 0) || f.all) && !f.dir)
		ft_printf("total %d\n", dir->total);
	while (++i < (int)dir->c_files)
	{
		file = (t_file *)files[i];
		if (fl)
			ft_putchar_n(' ', mcol->rast - file->name_len);
		else
			fl = 1;
		if (f.siz)
			ft_printf(" %d ", file->st.st_blocks);
		ft_printf("%s", file->name);
	}
	ft_printf("\n");
}

static void			print_mcol(t_nowdir *dir, t_dlist **files, t_mcol *mcol,\
					t_format f)
{
	int		i;
	int		j;
	t_file	*file;

	mcol->rowcount = (mcol->size / mcol->colcount) + 1;
	i = -1;
	if (f.siz && ((!f.all && dir->c_files > 0) || f.all) && !f.dir)
		ft_printf("total %d\n", dir->total);
	while (++i < mcol->rowcount)
	{
		j = -1;
		while ((++j < mcol->colcount) && i + (j * mcol->rowcount) < \
				mcol->size)
		{
			file = (t_file *)files[i + (j * mcol->rowcount)];
			if (f.siz)
			{
				ft_putchar_n(' ', dir->m_blck_size - file->blck_size);
				ft_printf("%d ", file->st.st_blocks);
			}
			ft_printf("%s", file->name);
			ft_putchar_n(' ', mcol->rast - (file->name_len + dir->m_blck_size));
		}
		ft_printf("\n");
	}
}

static void			init_arr_files(t_nowdir **dir, t_dlist ***files,\
					const t_format f, unsigned int *size)
{
	t_dlist	*list;
	int		i;
	t_file	*file;

	i = -1;
	list = (*dir)->file;
	while (list)
	{
		file = (t_file *)list->content;
		if (!(f.all) && file->name[0] == '.')
		{
			list = list->next;
			(*dir)->c_files--;
			continue ;
		}
		(*files)[++i] = list->content;
		(*size)++;
		list = list->next;
	}
}

void				put_mcol(const t_format f, t_nowdir *dir)
{
	t_mcol			mcol;
	t_dlist			**files;
	unsigned int	size;

	if (!(files = (t_dlist **)malloc(sizeof(t_dlist *) * dir->c_files)))
		exit(0);
	size = 0;
	init_arr_files(&dir, &files, f, &size);
	mcol.size = size;
	mcol.rast = dir->m_fname + 4 + dir->m_blck_size + 2;
	mcol.colcount = term.ws_col / (mcol.rast);
	if (mcol.colcount == 0)
		mcol.colcount = 1;
	if (dir->c_files * mcol.rast + (dir->c_files * dir->m_blck_size)\
		< term.ws_col)
		put_1str_mcol(dir, files, &mcol, f);
	else
		print_mcol(dir, files, &mcol, f);
	free_double_dlist(&files);
}
