/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:42:31 by aarchiba          #+#    #+#             */
/*   Updated: 2022/01/29 20:26:10 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	quote_init(t_data *tmp, t_var *q_var, int num_quote)
{
	q_var->temp_prev = NULL;
	q_var->q_ch = '\'';
	if (tmp->prev)
		q_var->temp_prev = &tmp->prev->once_quote;
	q_var->temp = &tmp->once_quote;
	if (num_quote == 2)
	{
		q_var->q_ch = '"';
		if (tmp->prev)
			q_var->temp_prev = &tmp->prev->double_quote;
		q_var->temp = &tmp->double_quote;
	}
}

void	quote_check(t_data *tmp, int num_quote)
{
	t_var	q_var;

	quote_init(tmp, &q_var, num_quote);
	if (tmp->sym == q_var.q_ch)
	{
		*q_var.temp = *q_var.temp_prev + 1;
		if ((*q_var.temp % 2) && tmp->prev)
		{
			if (space(tmp->prev->sym) || iscmd(tmp->prev->sym))
				tmp->args++;
		}
	}
}

void	arg_check(t_data *tmp)
{
	t_data	*prev;

	prev = tmp->prev;
	while (prev->rm == 1 || prev->rm == 2)
		prev = prev->prev;
	if ((!space(tmp->sym) && !iscmd(tmp->sym)) && (!iscmd(prev->sym) \
	&& space(tmp->prev->sym)))
		tmp->args++;
	if (tmp->red_addr)
	{
		if (tmp->args >= tmp->red_addr)
		{
			if (space(tmp->prev->sym))
			{
				tmp->red_addr = 0;
				tmp->redir = 0;
			}
		}
		if (tmp->args < tmp->red_addr - 1 && \
			(tmp->sym == '<' || tmp->sym == '>'))
			error_end(2);
	}
}

void	rm_check(t_data *tmp)
{
	if (tmp->sym == '$' && !(tmp->once_quote % 2))
	{
		tmp->var = 1;
		tmp->rm = 1;
	}
	if (space(tmp->sym))
	{
		tmp->var = 0;
		tmp->rm = 1;
	}
	if (tmp->sym == '\'' && !(tmp->double_quote % 2))
	{
		tmp->var = 0;
		tmp->rm = 2;
	}
	if (tmp->sym == '"' && !(tmp->once_quote % 2))
	{
		tmp->var = 0;
		tmp->rm = 2;
	}
	if (iscmd(tmp->sym))
	{
		tmp->var = 0;
		tmp->rm = 3;
	}
}
