/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:32:24 by aarchiba          #+#    #+#             */
/*   Updated: 2021/12/30 19:45:27 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_end(char *str, int flag)
{
	if (flag >= 0)
	{
		if (flag == 1)
		{
			printf ("Error: atoi/incorrect argument\n");
			exit (1);
		}
	}
}

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

void	and_check(char sym, t_data *prev, t_data *tmp)
{
	if (sym == '&' && !(prev->and_first))
		tmp->and_first = 1;
	else if (sym == '&' && prev->and_first)
	{
		tmp->and = prev->and + 1;
		tmp->and_first = 0;
	}
	else if (sym != '&' && prev->and_first)
		error_end(NULL, 1); //
	else
		tmp->and_first = 0;
}

void	quote_check(char sym, t_data *prev, t_data *tmp, int num_quote)
{
	char	f_char;
	int		tmp;
	int		tmp_prev;

	f_char = '\'';
	tmp_prev = prev->once_quote;
	tmp = tmp->once_quote;
	if (num_quote == 2)
	{
		f_char = '"';
		tmp = prev->double_quote;
	}
	if (sym == f_char)
		tmp = tmp_prev + 1;
}

t_data	*parse_it(char sym, t_data *prev)
{
	t_data	*tmp;
	int		i;

	i = -1;
	tmp = prev;
	// tmp = (t_data){};
	tmp->sym = sym;
	and_check(sym, prev, tmp);
	if (sym == '|' && prev->sym != '|')
		tmp->or = prev->or + 1;
	
}
