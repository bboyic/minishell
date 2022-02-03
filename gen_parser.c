/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 19:56:35 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/03 15:26:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static t_cmd	*combine(t_cmd *prev, t_data **sym, char **env, int *counter)
{
	t_cmd	*new;
	t_var	cntr;

	new = init_func(prev, &cntr, *sym);
	while (*sym)
	{
		if ((*sym)->cmd != *counter)
			break ;
		gen_check(sym, new, &cntr, env);
	}
	(*counter)++;
	return (new);
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
	if (!arg)
		error_end(3);
	save_point(arg, 2);
	i = 0;
	while (tmp)
	{
		arg[i++] = tmp->path;
		tmp = tmp->next;
	}
	arg[i] = NULL;
	return (arg);
}

t_cmd	*cmd_parse(t_data *sym, char ***env)
{
	t_cmd	*tmp;
	t_cmd	*head_tmp;
	t_cmd	*old_tmp;
	int		i;
	int		error;
/*ACONCHIT !!! {*/
	int		fd[2][2];
	int		red_fd[2];

	error = 0;
	fd[0][0] = -1;
	fd[0][1] = -1;
	fd[1][0] = -1;
	fd[1][1] = -1;
	red_fd[0] = -1;
	red_fd[1] = -1;
/*ACONCHIT !!! }*/
	i = 0;
	head_tmp = NULL;
	old_tmp = NULL;
	while (sym)
	{
		tmp = combine(old_tmp, &sym, *env, &i);
		save_point(tmp, 2);
		add_back_or_new_cmd(&head_tmp, tmp);
		tmp->argum = conv_to_str(tmp->args);
		save_point(tmp->argum, 1);
		//print_it(tmp);
		if (tmp->var_or == 1 && error == 0)
			return (head_tmp);
		if (tmp->var_or == 1)
			error = 0;
		if (error == 0)
		{
			if (!minishell(tmp, &(*env), fd, red_fd))
				error = 1;
		}
		// action
		old_tmp = tmp;
	}
	return (head_tmp);
}
