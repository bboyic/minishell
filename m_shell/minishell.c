/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconchit <aconchit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:32:20 by aarchiba          #+#    #+#             */
/*   Updated: 2022/01/26 11:49:32 by aconchit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_end(t_data *data, t_cmd *cmd, int flag)
{
	if (flag < 0)
	{
		flag *= -1;
	}
	if (flag >= 0)
	{
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
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_data	*tmp;
	t_cmd	*cmd;

	while (1)
	{
		str = readline("minishell$ ");
		tmp = sym_parse(str);
		cmd = cmd_parse(tmp);
		//minishell(cmd, NULL);
		cmd = cmd->next;
		//printf("==%s==\n", cmd->argum[0]);
	}
	return (0);
}

// "'Cat' >> 'helo. Txt' -e>> 1 > 2|  h'ea'd| wc -l &&echo '$USER' a";
// "$'Cat' >> 'hel"l"o. Txt' -e>> 1 > 2|  h'ea'd| wc -l &&echo '$USER' a"