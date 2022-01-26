/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconchit <aconchit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:32:41 by aarchiba          #+#    #+#             */
/*   Updated: 2022/01/26 11:20:58 by aconchit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	red_part_1(t_data *tmp)
{
	if (tmp->sym == '>' && !tmp->prev->red_first)
	{
		if (tmp->prev->her_first)
			error_end(NULL, NULL, 2);
		tmp->red_first = 1;
		return (0);
	}
	else if (tmp->sym == '<' && !tmp->prev->her_first)
	{
		if (tmp->prev->red_first)
			error_end(NULL, NULL, 2);
		tmp->her_first = 1;
		return (0);
	}
	else if (tmp->sym == '>' && tmp->prev->red_first)
	{
		tmp->red_first = tmp->prev->red_first + 1;
		return (0);
	}
	else if (tmp->sym == '<' && tmp->prev->her_first)
	{
		tmp->her_first = tmp->prev->her_first + 1;
		return (0);
	}
	return (1);
}

int	red_part_2(t_data *tmp)
{
	if (!(tmp->sym == '>') && tmp->prev->red_first == 1)
	{
		tmp->redir = 2;
		tmp->red_first = 0;
	}	
	else if (!(tmp->sym == '>') && tmp->prev->red_first == 2)
	{
		tmp->redir = 4;
		tmp->red_first = 0;
	}	
	else if (!(tmp->sym == '<') && tmp->prev->her_first == 1)
	{
		tmp->redir = 1;
		tmp->her_first = 0;
	}	
	else if (!(tmp->sym == '<') && tmp->prev->her_first == 2)
	{
		tmp->redir = 3;
		tmp->her_first = 0;
	}
	else
		return (1);
	tmp->red_addr = tmp->args + 1;
	tmp->red_counter++;
	return (0);
}

void	red_check(t_data *tmp)
{
	if ((tmp->prev->her_first > 2 || tmp->prev->red_first > 2) || \
		((tmp->prev->redir || tmp->prev->heredoc) && (tmp->sym == '>' || \
		tmp->sym == '<') && tmp->prev->rm != 1 && tmp->red_addr && \
		tmp->red_counter))
		error_end(NULL, NULL, 2);
	if (!red_part_1(tmp))
		return ;
	else if (!red_part_2(tmp))
		return ;
	else
	{
		tmp->her_first = 0;
		tmp->red_first = 0;
	}
}
