/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:33:42 by aarchiba          #+#    #+#             */
/*   Updated: 2022/01/25 16:23:29 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_back_or_new(t_data **lst, t_data *new)
{
	t_data	*last;

	last = *lst;
	if (!(*lst))
		*lst = new;
	else
	{
		while (last->next)
			last = last->next;
		last->next = new;
	}
	new->prev = last;
}

void	re_init(t_data *tmp)
{
	tmp->or = tmp->prev->or;
	tmp->var = tmp->prev->var;
	tmp->cmd = tmp->prev->cmd;
	tmp->and = tmp->prev->and;
	tmp->args = tmp->prev->args;
	tmp->redir = tmp->prev->redir;
	tmp->heredoc = tmp->prev->heredoc;
	tmp->red_addr = tmp->prev->red_addr;
	tmp->once_quote = tmp->prev->once_quote;
	tmp->red_counter = tmp->prev->red_counter;
	tmp->double_quote = tmp->prev->double_quote;
	if (tmp->prev->pipe_in_flag && tmp->prev->rm)
		tmp->pipe_in_flag = 1;
}

int	space(char sym)
{
	if ((sym >= 9 && sym <= 13) || sym == 32)
		return (1);
	return (0);
}

int	iscmd(char sym)
{
	if (sym == '|' || sym == '&' || sym == '>' || sym == '<')
		return (1);
	return (0);
}
