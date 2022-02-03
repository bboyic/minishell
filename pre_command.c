/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:39:19 by aarchiba          #+#    #+#             */
/*   Updated: 2022/01/29 20:26:58 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	and_check(t_data *tmp)
{
	if (tmp->sym == '&' && !(tmp->prev->and_first))
		tmp->and_first = 1;
	else if (tmp->sym == '&' && tmp->prev->and_first)
		tmp->and_first = tmp->prev->and_first + 1;
	else if ((tmp->sym != '&' && tmp->prev->and_first == 1) || \
		tmp->prev->and_first > 2)
		error_end(2);
	else if (tmp->sym != '&' && tmp->prev->and_first == 2)
	{
		tmp->and++;
		tmp->and_first = 2;
	}
	else
		tmp->and_first = 0;
}

static void	pipe_check(t_data *tmp)
{
	t_data	*prv;

	prv = tmp->prev;
	while (prv->rm)
	{
		prv = prv->prev;
		prv->pipe_out_flag = 1;
	}
	prv->pipe_out_flag = 1;
	tmp->prev->pipe_in_flag = 1;
	tmp->pipe_in_flag = 1;
	tmp->and_first = 0;
	tmp->or_first = 0;
	tmp->and = 0;
	tmp->or = 0;
}

void	or_check(t_data *tmp)
{
	if (tmp->sym == '|' && !(tmp->prev->or_first))
		tmp->or_first = 1;
	else if (tmp->sym == '|' && tmp->prev->or_first)
		tmp->or_first = tmp->prev->or_first + 1;
	else if (tmp->sym != '|' && tmp->prev->or_first == 1)
		pipe_check(tmp);
	else if (tmp->sym != '|' && tmp->prev->or_first == 2)
	{
		tmp->or = tmp->prev->or + 1;
		tmp->or_first = 0;
	}
	else
		tmp->or_first = 0;
}

void	cmd_check(t_data *tmp)
{
	if (tmp->prev->pipe_in_flag || (tmp->or != tmp->prev->or) || \
		(tmp->and != tmp->prev->and))
	{
		if (tmp->red_addr > tmp->args + 1)
			error_end(2);
		tmp->cmd++;
		tmp->args = 0;
		tmp->redir = 0;
		tmp->red_addr = 0;
		tmp->red_counter = 0;
	}
}
