/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsef.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 19:56:10 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/08/11 13:36:26 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	usage(const char flag)
{
	if (!ft_strchr("RtrlC1aufdsgq", flag))
	{
		ft_printf("ft_ls illegal option -- %c\n\
usage: ft_ls [-RtrlC1aufdsgq] [file ...]\n", flag);
		exit(0);
	}
}

static void	reduct_lines(char *flag, t_format *f)
{
	if (*flag == 'd')
		f->dir = 1;
	else if (*flag == 's')
		f->siz = 1;
	else if (*flag == 'g')
		f->ngu = 1;
	else if (*flag == 'q')
		f->ngw = 1;
	else if (*flag == 'a')
		f->all = 1;
	else if (*flag == 'u' && (f->tim = 0))
		f->tds = 1;
	else if (*flag == 'f' && (f->all = 1))
		f->nsr = 1;
	else if (*flag == 't' && (f->tds = 0) == 0)
		f->tim = 1;
	else if (*flag == 'r')
		f->rev = 1;
	else if (*flag == 'u' && (f->tim = 0))
		f->tds = 1;
	else if (*flag == 'f' && (f->all = 1))
		f->nsr = 1;
}

static void	parse_flags(char *flag, t_format *f)
{
	while (*flag)
	{
		reduct_lines(flag, f);
		if (*flag == 'R')
			f->rec = 1;
		else if (*flag == 'l' && (f->col = 0) == 0)
		{
			f->one = 0;
			f->lon = 1;
		}
		else if (*flag == 'C' && (f->lon = 0) == 0)
		{
			f->one = 0;
			f->col = 1;
		}
		else if (*flag == '1' && (f->lon = 0) == 0)
		{
			f->col = 0;
			f->one = 1;
		}
		else if (*flag == '-')
			break ;
		++flag;
		usage(*flag);
	}
}

int			parser(const int argc, char **argv, t_format *f)
{
	int i;

	i = 1;
	ft_bzero(f, sizeof(t_format));
	f->col = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-')
			parse_flags(++argv[i], f);
		else
			break ;
		++i;
	}
	return (i);
}
