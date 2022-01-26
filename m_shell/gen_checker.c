/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconchit <aconchit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:56:17 by aarchiba          #+#    #+#             */
/*   Updated: 2022/01/26 11:22:07 by aconchit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	gen_flag_check(t_data *sym, t_cmd *tmp, t_arg *local)
{
	if (sym->or)
		tmp->var_or = 1;
	if (sym->and)
		tmp->and = 1;
	if (sym->pipe_in_flag)
		tmp->pipe.in = 1;
	if (sym->pipe_out_flag)
		tmp->pipe.out = 1;
	if (sym->once_quote % 2)
		local->quote = 1;
	local->path = ft_chrjoin(local->path, sym->sym);
}

static int	break_mod(t_data **sym, t_var c, int mod)
{
	if ((mod == 2 && ((*sym)->args != c.a || (*sym)->red_addr)))
		return (1);
	if (mod == 1 && ((*sym)->red_addr != c.a || (*sym)->red_counter != c.n))
		return (1);
	if ((*sym)->cmd != c.m)
		return (1);
	return (0);
}

static t_arg	*gen_arg_check(t_data **sym, t_cmd *tmp, int mod)
{
	t_var	c;
	t_arg	*local;

	c.a = (*sym)->red_addr;
	c.n = (*sym)->red_counter;
	c.m = (*sym)->cmd;
	if (mod == 2)
		c.a = (*sym)->args;
	local = malloc(sizeof(t_arg));
	if (!local)
		error_end(*sym, NULL, -3);
	*local = (t_arg){};
	if ((*sym) && (*sym)->redir)
		local->type = (*sym)->redir;
	// if ((*sym) && (*sym)->heredoc)
	// 	local->type = HEREDOC;
	while (*sym)
	{
		if (break_mod(sym, c, mod) == 1)
			break ;
		gen_flag_check(*sym, tmp, local);
		*sym = (*sym)->next;
	}
	// if (mod == 1)
	// 	local->type = (*sym)->prev->redir;
	return (local);
}

void	gen_check(t_data **sym, t_cmd *tmp, t_var *cntr)
{
	t_arg	*arg;
	t_arg	*redir;

	if ((*sym)->red_counter != cntr->red_c && (*sym)->red_addr)
	{
		redir = gen_arg_check(sym, tmp, 1);
		add_back_or_new_arg(&tmp->redir, redir);
	}
	else if ((*sym)->args != cntr->arg_c)
	{
		arg = gen_arg_check(sym, tmp, 2);
		add_back_or_new_arg(&tmp->args, arg);
	}
}

char	**conv_to_str(t_arg *args)
{
	int		i;
	char	**arg;
	t_arg	*tmp;

	i = 0;
	tmp = args;
	while (tmp && i++ >= 0)
		tmp = tmp->next;
	tmp = args;
	arg = malloc (sizeof(char *) * (i + 1));
	i = 0;
	while (tmp)
	{
		arg[i++] = tmp->path;
		// if (!tmp->type)
		// 	arg[i - 1] = ;
		tmp = tmp->next;
	}
	arg[i] = NULL;
	return (arg);
}
