/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:56:17 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/03 15:21:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static void	var_check(t_data **sym, t_arg *local, char **env)
{
	t_env	*list_env;
	t_env	*tmp_env;

	while ((*sym)->var && !(*sym)->rm)
	{
		local->tmp_var = ft_chrjoin(local->tmp_var, (*sym)->sym);
		(*sym) = (*sym)->next;
		if (!*sym)
			break ;
	}
	list_env = ft_env_to_list(env);
	tmp_env = list_env;
	while (list_env)
	{
		if (!ft_strcmp(list_env->key, local->tmp_var))
		{
			local->path = ft_strjoin(local->path, list_env->value);
			break ;
		}
		list_env = list_env->next;
	}
	if (local->tmp_var)
		free (local->tmp_var);
	kill_env(tmp_env);
}

static void	gen_flag_check(t_data **sym, t_cmd *tmp, t_arg *local, char **env)
{
	int		i;

	if (!(*sym)->rm)
	{
		if ((*sym)->or)
			tmp->var_or = 1;
		if ((*sym)->and)
			tmp->and = 1;
		if ((*sym)->pipe_in_flag)
			tmp->pipe.in = 1;
		if ((*sym)->pipe_out_flag)
			tmp->pipe.out = 1;
		i = -1;
		if ((*sym)->var)
			var_check(sym, local, env);
		if (*sym && !(*sym)->rm)
			local->path = ft_chrjoin(local->path, (*sym)->sym);
	}
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

static t_arg	*gen_arg_check(t_data **sym, t_cmd *tmp, char **env, int mod)
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
		error_end(3);
	*local = (t_arg){};
	if (mod == 1)
		local->type = (*sym)->redir;
	while (*sym)
	{
		if (break_mod(sym, c, mod) == 1)
			break ;
		gen_flag_check(sym, tmp, local, env);
		if (*sym)
			*sym = (*sym)->next;
	}
	return (local);
}

void	gen_check(t_data **sym, t_cmd *tmp, t_var *cntr, char **env)
{
	t_arg	*arg;
	t_arg	*redir;

	if ((*sym)->red_counter != cntr->red_c && (*sym)->red_addr)
	{
		redir = gen_arg_check(sym, tmp, env, 1);
		save_point(redir, 1);
		save_point(redir->path, 1);
		add_back_or_new_arg(&tmp->redir, redir);
	}
	else if ((*sym)->args != cntr->arg_c)
	{
		arg = gen_arg_check(sym, tmp, env, 2);
		save_point(arg, 1);
		save_point(arg->path, 1);
		add_back_or_new_arg(&tmp->args, arg);
	}
}
