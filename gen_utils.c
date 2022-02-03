/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 21:54:46 by aarchiba          #+#    #+#             */
/*   Updated: 2022/01/30 19:21:12 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_back_or_new_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

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

void	add_back_or_new_arg(t_arg **lst, t_arg *new)
{
	t_arg	*last;

	last = *lst;
	if (!(*lst))
		*lst = new;
	else
	{
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

t_cmd	*init_func(t_cmd *prev, t_var *cntr, t_data *sym)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		error_end(3);
	*new = (t_cmd){};
	new->redir = NULL;
	new->args = NULL;
	cntr->red_c = sym->red_counter;
	cntr->arg_c = sym->args - 1;
	return (new);
}
