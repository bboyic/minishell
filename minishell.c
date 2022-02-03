/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:32:20 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/03 15:25:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	kill_env(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = temp;
	}
}

void	error_end(int flag)
{
	t_malloc_c	*tmp;

	tmp = save_point(NULL, 0);
	clear_point(tmp);
	if (flag == 1)
	{
		printf ("Error: atoi/incorrect argument\n");
		exit (1);
	}
	if (flag == 2)
	{
		printf ("Error: parse error\n");
		exit (1);
	}
	if (flag == 3)
	{
		printf ("Error: malloc error\n");
		exit (1);
	}
}

void	save_type(t_malloc_c **head, t_malloc_c *new, t_malloc_c *tmp, int flag)
{
	if (!*head)
		*head = new;
	else if (flag == 2)
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else if (flag == 1)
	{
		new->next = *head;
		*head = new;
	}
}

t_malloc_c	*save_point(void *mal_p, int flag)
{
	static t_malloc_c	*head;
	t_malloc_c			*new;
	t_malloc_c			*tmp;

	if (!flag)
		return (head);
	if (!mal_p)
	{
		head = NULL;
		return (head);
	}
	new = malloc(sizeof(t_malloc_c));
	if (!new)
		error_end(3);
	*new = (t_malloc_c){};
	new->point = mal_p;
	save_type(&head, new, tmp, flag);
	return (head);
}

void	clear_point(t_malloc_c *malloc_h)
{
	void	*tmp;

	while (malloc_h)
	{
		tmp = malloc_h->next;
		free(malloc_h->point);
		free(malloc_h);
		malloc_h = tmp;
	}
}

void	ft_handler(int signum, siginfo_t *siginfo, void *arg) // ACONCHIT !!!
{
	if (signum == 11)
		exit(0);
	if (signum == SIGINT)
		printf("\n\e[1;32mMINISHELL$\e[0;37m ");
	if (signum == SIGPIPE)
		exit(0);
}

int	ft_signal(char **cmd) //ACONCHIT !!!
{
	struct sigaction	sig;
	int					i;


	i = 0;
	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = ft_handler;
	sigaction(11, &sig, (void *)cmd); //CTRL-D
	sigaction(SIGINT, &sig, (void *)cmd); //CTRL-C
	// sigaction(SIGSTOP, &sig, (void *)cmd);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char	*str;
	t_data	*tmp;
	t_cmd	*cmd;

	ft_signal(NULL);// ACONCHIT!!! for signal
	while (1)
	{
		save_point(NULL, 4);
		str = readline("\e[1;32mMINISHELL$\e[0;37m ");
		add_history(str); // History for readline
		tmp = sym_parse(str);
		//pre_res_print(tmp);
		cmd = cmd_parse(tmp, &env);// ACONCHIT !!
		error_end(4);
	}
	// free(env);
	return (0);
}


// "'Cat' >> 'helo. Txt' -e>> 1 > 2|  h'ea'd| wc -l &&echo '$USER' a";
// "$'Cat' >> 'hel"l"o. Txt' -e>> 1 > 2|  h'ea'd| wc -l &&echo '$USER' a"