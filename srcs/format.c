/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 13:19:07 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/08/11 16:33:06 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		put_old_time_file(const char *ctimef, char *timef)
{
	timef[0] = ctimef[4];
	timef[1] = ctimef[5];
	timef[2] = ctimef[6];
	timef[3] = ' ';
	timef[4] = ctimef[8];
	timef[5] = ctimef[9];
	timef[6] = ' ';
	timef[7] = ' ';
	timef[8] = ctimef[20];
	timef[9] = ctimef[21];
	timef[10] = ctimef[22];
	timef[11] = ctimef[23];
	timef[12] = '\0';
	ft_putstr(timef);
}

void			put_time(const char *ctimef,\
		const long mtime, const long atime, const long c_time)
{
	time_t	ttime;
	char	timef[13];

	time(&(ttime));
	if (ttime - mtime > 15552000 || ttime - mtime < -3600)
	{
		put_old_time_file(ctimef, timef);
		return ;
	}
	timef[1] = ctimef[5];
	timef[0] = ctimef[4];
	timef[2] = ctimef[6];
	timef[3] = ' ';
	timef[4] = ctimef[8];
	timef[5] = ctimef[9];
	timef[6] = ' ';
	timef[7] = ctimef[11];
	timef[8] = ctimef[12];
	timef[9] = ctimef[13];
	timef[10] = ctimef[14];
	timef[11] = ctimef[15];
	timef[12] = '\0';
	ft_putstr(timef);
}

static void		put_blck_link_size(const __uint32_t val, const int l, \
								const int len)
{
	char	*n;

	n = ft_itoa(val);
	ft_putchar_n(' ', len - l);
	ft_putstr(n);
	write(1, " ", 1);
	free(n);
	return ;
}

static void		put_usr_grp(const char *val, const int l, const int len)
{
	ft_putstr(val);
	ft_putchar_n(' ', len - l);
	write(1, "  ", 2);
}

void			formatter(const t_file *fi, const t_format f, const t_len *l)
{
	char	buf[NAME_MAX];

	f.siz ? put_blck_link_size(fi->det->block, fi->det->l->blck, l->blck) : 0;
	ft_putstr(fi->det->rights);
	write(1, " ", 1);
	put_blck_link_size(fi->st.st_nlink, fi->det->l->link, l->link);
	if (!f.ngu)
	{
		put_usr_grp(fi->det->user, fi->det->l->user, l->user);
		if (!f.ngw)
			put_usr_grp(fi->det->group, fi->det->l->grou, l->grou);
	}
	put_blck_link_size(fi->st.st_size, fi->det->l->size, l->size);
	help_put_time(fi, f.tds);
	if (fi->det->rights[0] == 'l')
	{
		ft_bzero(buf, NAME_MAX);
		readlink(fi->f_path, buf, NAME_MAX);
		ft_printf(" %s -> %s\n", fi->name, buf);
	}
	else
		ft_printf(" %s\n", fi->name);
}
