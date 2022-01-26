/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconchit <aconchit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 19:56:35 by aarchiba          #+#    #+#             */
/*   Updated: 2022/01/26 11:49:18 by aconchit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*combine(t_cmd *prev, t_data **sym, int *counter)
{
	t_cmd	*new;
	t_var	cntr;

	new = init_func(prev, &cntr, *sym);
	while (*sym)
	{
		if ((*sym)->cmd != *counter)
			break ;
		gen_check(sym, new, &cntr);
	}
	(*counter)++;
	return (new);
}

t_cmd	*cmd_parse(t_data *sym)
{
	t_cmd	*tmp;
	t_cmd	*head_tmp;
	t_cmd	*old_tmp;
	int		fd[2][2];
	int		red_fd[2];
	int		i;

	fd[0][0] = -1;
	fd[0][1] = -1;
	fd[1][0] = -1;
	fd[1][1] = -1;
	red_fd[0] = -1;
	red_fd[1] = -1;
	i = 0;
	head_tmp = NULL;
	old_tmp = NULL;
	while (sym)
	{
		tmp = combine(old_tmp, &sym, &i);
		add_back_or_new_cmd(&head_tmp, tmp);
		tmp->argum = conv_to_str(tmp->args);
		minishell(tmp, NULL, fd, red_fd);
		//print_it(tmp);
		// action
		old_tmp = tmp;
	}
	return (head_tmp);
}
