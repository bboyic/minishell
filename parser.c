/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:32:24 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/03 15:20:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static void	pre_check_first(t_data *tmp)
{
	if (iscmd(tmp->sym))
		error_end(2);
	if (tmp->sym == '\'')
		tmp->once_quote++;
	if (tmp->sym == '"')
		tmp->double_quote++;
	if (tmp->sym == '"' || tmp->sym == '\'')
		tmp->rm = 2;
	if (tmp->sym == '$')
	{
		tmp->var = 1;
		tmp->rm = 2;
	}
}

void	pre_check(t_data *tmp)
{
	if (!tmp->double_quote % 2)
		quote_check(tmp, 1);
	if (!tmp->once_quote % 2)
		quote_check(tmp, 2);
	if (!(tmp->double_quote % 2) && !(tmp->once_quote % 2))
	{
		if (iscmd(tmp->sym) || iscmd(tmp->prev->sym))
		{
			and_check(tmp);
			or_check(tmp);
			cmd_check(tmp);
			red_check(tmp);
		}
		arg_check(tmp);
	}
	rm_check(tmp);
}

t_data	*pre_parse_it(char sym, t_data *prev)
{
	t_data	*tmp;

	tmp = malloc(sizeof(t_data));
	if (!tmp)
		error_end(3);
	*tmp = (t_data){};
	tmp->sym = sym;
	tmp->prev = prev;
	if (tmp->prev)
	{
		re_init(tmp);
		pre_check(tmp);
	}
	else
		pre_check_first(tmp);
	return (tmp);
}

static void	last_check(t_data *tmp)
{
	t_data	*prv;

	prv = tmp->prev;
	while (prv && (prv->rm == 1 || prv->rm == 2))
		if (prv->prev)
			prv = prv->prev;
	if ((tmp->sym == '>' || tmp->sym == '<'))
		error_end(2);
	else if (space(tmp->sym))
		if (prv && (prv->sym == '>' || prv->sym == '<'))
			error_end(2);
}

t_data	*sym_parse(char *str)
{
	int		i;
	t_data	*preparse;
	t_data	*tmp;
	t_data	*tmp_old;

	i = -1;
	preparse = NULL;
	tmp_old = NULL;
	while (str[++i])
	{
		tmp = pre_parse_it(str[i], tmp_old);
		save_point(tmp, 2);
		if (!str[i + 1])
			last_check(tmp);
		add_back_or_new(&preparse, tmp);
		tmp_old = tmp;
	}
	return (preparse);
}
