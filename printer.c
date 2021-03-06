/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:55:10 by aarchiba          #+#    #+#             */
/*   Updated: 2022/01/30 21:19:48 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pre_res_print(t_data *tmp)
{
	int	i;

	i = 0;
	while (tmp)
	{
		printf("num %3d - sym : %4c -> \
n_cmd %d | n_arg %d | q %d/%d | redir : %d(%d/%d) add: %d cnt: %d var : %d| \
pipe_i : %d | pipe_o : %d | or : %d(pr:%d) | and : %d(pr:%d) | rm : %d\n", \
i++, tmp->sym, tmp->cmd, tmp->args, tmp->once_quote, tmp->double_quote, \
tmp->redir, tmp->red_first, tmp->her_first, tmp->red_addr, tmp->red_counter, \
tmp->var, tmp->pipe_in_flag, tmp->pipe_out_flag, tmp->or, tmp->or_first, \
tmp->and, tmp->and_first, tmp->rm);
		tmp = tmp->next;
	}
}

static char	*redir_print(t_cmd *tmp)
{
	char	*s;

	if (tmp->redir->type == 1)
		s = "left redirect";
	else if (tmp->redir->type == 2)
		s = "right redirect";
	else if (tmp->redir->type == 3)
		s = "heredoc";
	else if (tmp->redir->type == 4)
		s = "d_right redirect";
	return (s);
}

void	print_it(t_cmd *cmd)
{
	int		i;
	char	*s;
	t_cmd	*tmp;

	i = 0;
	tmp = cmd;
	printf("\nargs :\n\n");
	while (tmp->args)
	{
		printf("%d. %s\n", i++, tmp->args->path);
		tmp->args = tmp->args->next;
	}
	tmp = cmd;
	i = 0;
	printf("\nredirects :\n\n");
	while (tmp->redir)
	{
		s = redir_print(tmp);
		printf("%d. type : %s , value : %s\n", i++, s, tmp->redir->path);
		tmp->redir = tmp->redir->next;
	}
	printf("\nflags :\n\n");
	printf("and : %d\nor : %d\npipe in(%d)/out(%d)\n", \
		cmd->and, cmd->var_or, cmd->pipe.in, cmd->pipe.out);
}

void	print_addr(void)
{
	t_malloc_c	*tmp;
	int			i;

	tmp = save_point(NULL, 0);
	i = 0;
	printf ("\n*******************************\n");
	while (tmp)
	{
		printf("%2d : %p\n", i++, tmp->point);
		tmp = tmp->next;
	}
	printf ("\n*******************************\n");
}
