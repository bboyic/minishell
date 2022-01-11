/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:32:24 by aarchiba          #+#    #+#             */
/*   Updated: 2022/01/11 22:07:05 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_back_or_new(t_list **lst, void *content, int fd)
{
	t_list	*last;
	t_list	*tmp;

	last = *lst;
	tmp = malloc(sizeof(t_list));
	if (!tmp)
		return ;
	*tmp = (t_list){};
	if (!(*lst))
		*lst = tmp;
	else
	{
		while (last->next)
			last = last->next;
		last->next = tmp;
	}
}

void	and_check(t_data *tmp)
{
	if (tmp->sym == '&' && !(tmp->prev->and_first))
		tmp->and_first = 1;
	else if (tmp->sym == '&' && tmp->prev->and_first)
	{
		tmp->and = tmp->prev->and + 1;
		tmp->and_first = 0;
	}
	else if (tmp->sym != '&' && tmp->prev->and_first)
		error_end(NULL, 1);//
	else
		tmp->and_first = 0;
}

void	or_check(t_data *tmp)
{
	if (tmp->sym == '|' && !(tmp->prev->or_first))
		tmp->or_first = 1;
	else if (tmp->sym == '|' && tmp->prev->or_first)
	{
		tmp->or = tmp->prev->or + 1;
		tmp->or_first = 0;
	}
	else if (tmp->sym != '|' && tmp->prev->or_first)
	{
		tmp->prev->pipe_out_flag = 1;
		tmp->pipe_in_flag = 1;
	}
	else
		tmp->or_first = 0;
}

void	quote_check(t_data *tmp, int num_quote)
{
	char	f_char;
	int		*temp;
	int		*temp_prev;

	f_char = '\'';
	temp_prev = &tmp->prev->once_quote;
	temp = &tmp->once_quote;
	if (num_quote == 2)
	{
		f_char = '"';
		temp = &tmp->prev->double_quote;
	}
	if (tmp->sym == f_char)
		*temp = temp_prev + 1;
}

void	arg_check(t_data *tmp)
{
	if (tmp->sym != ' ' && tmp->prev->sym == ' ')
		tmp->args++;
}

void	cmd_check(t_data *tmp)
{
	if (tmp->pipe_in_flag || tmp->or || tmp->and)
		tmp->cmd++;
}

t_data	*parse_it(char sym, t_data *prev)
{
	t_data	*tmp;
	int		i;

	i = -1;
	tmp = prev;
	*tmp = (t_data){};
	tmp->sym = sym;
	quote_check(tmp, 1);
	quote_check(tmp, 2);
	if (!(tmp->double_quote % 2) && !(tmp->once_quote % 2))
	{
		and_check(tmp);
		or_check(tmp);
	}
	arg_check(tmp);
	cmd_check(tmp);
	return (tmp);
}
