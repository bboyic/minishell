/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:32:24 by aarchiba          #+#    #+#             */
/*   Updated: 2022/01/25 17:55:34 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (!tmp->rm)
			add_back_or_new(&preparse, tmp);
		tmp_old = tmp;
	}
	return (preparse);
}

static void	pre_check_first(t_data *tmp)
{
	if (iscmd(tmp->sym))
		error_end(NULL, NULL, 2);
	if (tmp->sym == '\'')
		tmp->once_quote++;
	if (tmp->sym == '"')
		tmp->double_quote++;
	if (tmp->sym == '"' || tmp->sym == '\'')
		tmp->rm = 2;
	if (tmp->sym == '$')
		tmp->var = 1;
}

t_data	*pre_parse_it(char sym, t_data *prev)
{
	t_data	*tmp;

	tmp = malloc(sizeof(t_data));
	if (!tmp)
		error_end(NULL, NULL, 3);
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
