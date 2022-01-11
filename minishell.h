/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:32:22 by aarchiba          #+#    #+#             */
/*   Updated: 2022/01/11 18:12:07 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h> 
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h> // ?
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <pthread.h>
# include <semaphore.h>  
# include "libft/libft.h"

typedef struct s_pipe
{
	int	in;
	int	out;
}	t_pipe;

typedef struct s_redir
{
	int	red_l;
	int	red_r;
	int	d_res;
	int	heridog;
}	t_redir;

typedef struct s_data
{
	struct s_data	*next;
	struct s_data	*prev;
	char			sym;
	int				pipe_out_flag;
	int				pipe_in_flag;
	int				once_quote;
	int				double_quote;
	int				or;
	int				or_first;
	int				and;
	int				and_first;
	int				args;
	int				cmd;
}	t_data;

typedef struct s_cmd
{
	char	**args;
	t_pipe	*pipe;
	t_redir	*redir;
	int		or;
}	t_cmd;

void	error_end(char *str, int flag);
#endif