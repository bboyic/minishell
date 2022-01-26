/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconchit <aconchit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:32:22 by aarchiba          #+#    #+#             */
/*   Updated: 2022/01/26 11:49:43 by aconchit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h> 
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <pthread.h>
# include <semaphore.h>  
# include "libft/libft.h"

# define L_REDIR 1
# define R_REDIR 2
# define HEREDOC 3
# define DR_REDIR 4

typedef struct s_var
{
	int		red_c;
	int		arg_c;
	int		a;
	int		n;
	int		m;
	int		*temp;
	int		*temp_prev;
	char	q_ch;
}	t_var;

typedef struct s_pipe
{
	int	in;
	int	out;
}	t_pipe;

typedef struct s_arg
{
	struct s_arg	*next;
	int				type;
	int				quote;
	char			*path;
}	t_arg;

typedef struct s_cmd
{
	struct s_cmd	*next;
	struct s_cmd	*prev;
	char			**argum;
	t_pipe			pipe;
	t_arg			*args;
	t_arg			*redir;
	int				var_or;
	int				and;
}	t_cmd;

typedef struct s_data
{
	struct s_data	*next;
	struct s_data	*prev;
	char			sym;
	int				pipe_out_flag;
	int				pipe_in_flag;
	int				double_quote;
	int				once_quote;
	int				red_counter;
	int				red_first;
	int				her_first;
	int				red_addr;
	int				heredoc;
	int				redir;
	int				and_first;
	int				or_first;
	int				and;
	int				or;
	int				args;
	int				var;
	int				cmd;
	int				rm;
}	t_data;

/* general */
void	error_end(t_data *data, t_cmd *cmd, int flag);

/* pre utils */
void	re_init(t_data *tmp);
int		space(char sym);
int		iscmd(char sym);
void	add_back_or_new(t_data **lst, t_data *new);

/* pre redirect */
int		red_part_1(t_data *tmp);
int		red_part_2(t_data *tmp);
void	red_check(t_data *tmp);

/* pre commands */
void	and_check(t_data *tmp);
void	or_check(t_data *tmp);
void	cmd_check(t_data *tmp);

/* pre arguments */
void	rm_check(t_data *tmp);
void	arg_check(t_data *tmp);
void	quote_check(t_data *tmp, int num_quote);

/* pre parser */
t_data	*sym_parse(char *str);
t_data	*pre_parse_it(char sym, t_data *prev);
void	pre_check(t_data *tmp);

/* gen utils */
void	add_back_or_new_cmd(t_cmd **lst, t_cmd *new);
void	add_back_or_new_arg(t_arg **lst, t_arg *new);
t_cmd	*init_func(t_cmd *prev, t_var *cntr, t_data *sym);

/* printer */
void	pre_res_print(t_data *tmp);
void	print_it(t_cmd *cmd);

/* gen checker & gen parser*/
void	gen_check(t_data **sym, t_cmd *tmp, t_var *cntr);
t_cmd	*cmd_parse(t_data *sym);
char	**conv_to_str(t_arg *args);

//void	ft_putstr_fd(char *str, int fd);
//size_t	ft_strlen(const char *s);
int		ft_cd(char *path);
int		ft_echo(char **av);
int		ft_env(char **env);
//char	**ft_split(char const *s, char c);
//int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
//char	*ft_strjoin(char const *s1, char const *s2);
//char	*ft_strdup(const char *s1);
int		ft_pwd(void);
int	minishell(t_cmd *command, char **env, int fd[2][2], int red_fd[2]);


#endif