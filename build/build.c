#include "../minishell.h"

/*
	==OUTPUT FUNCTION==
	void ft_putstr(char str);

	_DESCRIPTION_:
	uses write() for
	output str

	_RETURN_:
	NOTHING
*/

t_free	*ft_new_free_list(void *pointer)
{
	t_free	*list;

	list = (t_free *)malloc(sizeof(t_free));
	if (!list)
		return (NULL);
	list->next = NULL;
	list->pointer = pointer;
	return (list);
}

void	ft_add_free_list(t_free **head, void *pointer)
{
	t_free	*list;

	if (!*head)
	{
		*head = ft_new_free_list(pointer);
		if (!*head)
			return ;
		return ;
	}
	list = *head;
	while (list->next)
	{
		list = list->next;
	}
	list->next = ft_new_free_list(pointer);
}

void	ft_pfree(t_cmd **command, char *pointer)
{
	t_cmd *cmd;

	cmd = *command;
	ft_add_free_list(&cmd->free, (void *)pointer);
}

void	ft_ppfree(t_cmd **command, char **pointer)
{
	t_cmd *cmd;

	cmd = *command;
	ft_add_free_list(&cmd->free, (void *)pointer);
	while (*pointer)
		ft_pfree(&cmd, *(pointer++));
}

void	ft_putstr_fd(char *str, int fd)
{
	while(*str)
		write(fd, str++, 1);
}

int	ft_check_bin(char *path)
{
	while (*path)
	{
		if (*path == '/')
			return (1);
		++path;
	}
	return (0);
}

char	*ft_return_path(char **paths, char *arg, t_cmd *command)
{
	int		index;
	char	*check_path;

	index = 0;
	while (paths[index])
	{
		check_path = ft_stdstrjoin(paths[index], arg);
		ft_pfree(&command, check_path);
		if (!access(check_path, 1))
			return (check_path);
		++index;
	}
	return (NULL);
}

char	*ft_find_command(t_cmd *command)
{
	char	*path;
	char	**paths;
	char	*arg;

	if (!access(command->argum[0], 1))
	{
		if (!ft_check_bin(command->argum[0]))
			return (NULL);
		return (command->argum[0]);
	}
	path = getenv("PATH");
	paths = ft_split(path, ':');
	ft_ppfree(&command, paths);
	arg = ft_stdstrjoin("/", command->argum[0]);
	ft_pfree(&command, arg);
	return (ft_return_path(paths, arg, command));
}

int	ft_check_out(t_cmd command)
{
	while (command.redir && command.redir->path)
	{
		if (command.redir->type == DR_REDIR || command.redir->type == R_REDIR)
			return (1);
		command.redir = command.redir->next;
	}
	return (0);
}

int	ft_check_in(t_cmd command)
{
	while (command.redir && command.redir->path)
	{
		if (command.redir->type == L_REDIR || command.redir->type == HEREDOC)
			return (1);
		command.redir = command.redir->next;
	}
	return (0);
}

int	ft_pipex(int red_pipe[2], int fd[2][2], t_cmd *command)
{
	if (ft_check_out(*command))
		command->pipe.out = 0;
	if (ft_check_in(*command))
		command->pipe.in = 0;
	if (command->pipe.out == 1)
	{
		close(fd[0][0]);
		fd[0][0] = -1;
		dup2(fd[0][1], 1);
	}
	if (command->pipe.in == 1)
	{
		dup2(fd[1][0], 0);
		close(fd[1][1]);
		fd[1][1] = -1;
		close(fd[0][1]);
		fd[0][1] = -1;
	}
	if (ft_check_in(*command))
	{
		close(red_pipe[1]);
		dup2(red_pipe[0], 0);
		close(red_pipe[0]);
	}
	return (1);
}

int ft_close(int fd[2][2])
{
	if (fd[0][0] != -1)
		close(fd[0][0]);
	if (fd[0][1] != -1)
		close(fd[0][1]);
	if (fd[1][0] != -1)
		close(fd[1][0]);
	if (fd[1][1] != -1)
		close(fd[1][1]);
	fd[0][0] = -1;
	fd[0][1] = -1;
	fd[1][0] = -1;
	fd[1][1] = -1;
	return (1);
}

int	ft_close_pipe(int fd[2][2], t_cmd command)
{
	if (command.pipe.in == 1)
	{
		close(fd[1][0]);
		fd[1][0] = -1;
		close(fd[1][1]);
		fd[1][1] = -1;
	}
	return (1);
}

int ft_open_redir_in(int *in, int *her, int mode, t_arg *redir)
{
	int heredoc;
	int infile;

	if (redir->type == L_REDIR && mode == 1)
	{
		heredoc = 0;
		if (infile != -1)
			close(infile);
		infile = open(redir->path, O_RDONLY);
		if (infile == -1)
			return (0);
	}
	if (redir->type == HEREDOC && mode == 1)
		heredoc = 1;
	*her = heredoc;
	*in = infile;
	return (0);
}

int ft_open_redir_out(int *out, int mode, t_arg *redir)
{
	int outfile;

	if (redir->type == R_REDIR && mode == 0)
	{
		if (outfile != -1)
			close(outfile);
		outfile = open(redir->path, O_WRONLY | O_CREAT | O_TRUNC , S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (outfile == -1)
			return (0);
	}
	if (redir->type == DR_REDIR && mode == 0)
	{
		if (outfile != -1)
			close(outfile);
		outfile = open(redir->path, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (outfile == -1)
			return (0);
	}
	*out = outfile;
	return (0);
}

int	ft_apply_redirect(int infile, int outfile, int heredoc, int mode)
{
	char	buf;
	int		byte;

	if (infile != -1 && !heredoc && mode == 1)
	{
		while (byte != 0)
		{
			byte = read(infile, &buf, 1);
			if (byte == -1)
				return (0);
			if (byte)
				write(1, &buf, 1);
		}
	}
	if (outfile != -1 && mode == 0)
	{
		dup2(outfile, 1);
		close(outfile);
	}
	if (infile != -1)
		close(infile);
	byte = 1;
	return (0);
}

int	ft_redir(t_arg *redir, int mode)
{
	int		infile;
	int		outfile;
	int		heredoc;

	heredoc = 0;
	infile = -1;
	outfile = -1;
	while (redir)
	{
		ft_open_redir_out(&outfile, mode, redir);
		ft_open_redir_in(&infile, &heredoc, mode, redir);
		redir = redir->next;
	}
	ft_apply_redirect(infile, outfile, heredoc, mode);
	if (heredoc)
		return (HEREDOC);
	return (1);
}

char	*ft_heredoc(t_arg *redir, t_cmd *cmd)
{
	char	*str;
	char	*final;

	final = NULL;
	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			str = readline("> ");
			final = ft_strdup("");
			ft_pfree(&cmd, final);
			while (ft_strcmp(str, redir->path))
			{
				final = ft_stdstrjoin(final, str);
				ft_pfree(&cmd, final);
				final = ft_stdstrjoin(final, "\n");
				ft_pfree(&cmd, final);
				str = readline("> ");
			}
		}
		redir = redir->next;
	}
	return (final);
}

void	ft_system(t_cmd *command, char **env)
{
	if (!ft_strcmp(command->argum[0], "echo"))
	{
		ft_echo(command->argum);
		exit(0);
	}
	if (!ft_strcmp(command->argum[0], "env"))
	{
		ft_env(env);
		exit(0);
	}
	if (!ft_strcmp(command->argum[0], "pwd"))
	{
		ft_pwd();
		exit(0);
	}
	if (!ft_strcmp(command->argum[0], "export"))
	{
		ft_export(env, &command->argum[1]);
		exit(0);
	}
	// if (!ft_strcmp(command->argum[0], "unset"))
	// {
	// 	ft_unset(env, &command->argum[1]);
	// 	exit(0);
	// }
}

void	ft_free_all(t_cmd *cmd)
{
	t_free	*temp;
	while (cmd->free)
	{
		free(cmd->free->pointer);
		temp = cmd->free;
		cmd->free = cmd->free->next;
		free(temp);
	}
}

void	ft_child(t_cmd *command, int fd[2][2], int red_pipe[2], char **env)
{
	char	*path;

	if (command->redir)
			ft_redir(command->redir, 0);
	if (command->argum)
	{
		ft_pipex(red_pipe, fd, command);
		ft_close(fd);
		ft_system(command, env);
		path = ft_find_command(command);
		if (!path)
		{
			ft_putstr_fd(command->argum[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			ft_free_all(command);
			exit (-1);
		}
		path = ft_strdup(path);
		ft_free_all(command);
		if (execve(path, command->argum, env) == -1)
		{
			write(2, "error\n", 6);
			exit(1);
		}
	}
	else
		exit(0);
}

int	ft_wait_processes(int len_processes)
{
	int	status;
	int exit_status;

	exit_status = 1;
	while (len_processes-- > 0)
	{
		wait(&status);
		if (WEXITSTATUS(status))
			exit_status = 0;
		if (WTERMSIG(status) == SIGSEGV)
		{
			ft_putstr_fd("Error: Segmentation fault\n", 2);
			exit_status = 0;
		}
		if (WTERMSIG(status) == SIGABRT)
		{
			ft_putstr_fd("Error: Abort\n", 2);
			exit_status = 0;
		}
	}
	return(exit_status);
}

int	ft_redir_in(t_cmd *command, int fd[2][2], int red_pipe[2], char *heredoc)
{
	int	redir_status;
	int	fork_id;

	fork_id = fork();
	if (fork_id == 0)
	{
		if (command->redir)
		{
			close(red_pipe[0]);
			dup2(red_pipe[1], 1);
			close(red_pipe[1]);
			fd[0][1] = -1;
			redir_status = ft_redir(command->redir, 1);
			if (redir_status == HEREDOC)
				ft_putstr_fd(heredoc, 1);
			ft_close(fd);
		}
		ft_free_all(command);
		exit(0);
	}
	return (1);
}

int	ft_process_setup(int fd[2][2], int red_pipe[2], int *len_processes)
{
	ft_close(fd);
	close(red_pipe[0]);
	close(red_pipe[1]);
	if (ft_wait_processes(*len_processes) == 0)
	{
		*len_processes = 0;
		return (-1);
	}
	*len_processes = 0;
	return (1);
}

int	ft_system_parent(t_cmd *command, char ***env)
{
	if (command->argum && !ft_strcmp(command->argum[0], "cd"))
	{
		ft_cd(command->argum[1]);
		return (1);
	}
	 if (!ft_strcmp(command->argum[0], "export") && command->argum[1])
	{
		*env = ft_export(*env, &command->argum[1]);
		return (1);
	}
	if (!ft_strcmp(command->argum[0], "unset"))
	{
		*env = ft_unset(*env, &command->argum[1]);
		return (1);
	}
	return (0);
}

int	ft_execute_command(t_cmd *command, char ***env, int fd[2][2], int red_pipe[2])
{
	static int	len_processes = 0;
	int			fork_id;
	char		*heredoc;
	int			retrn;

	heredoc = NULL;
	retrn = 1;
	if (ft_system_parent(command, &(*env)))
		return (1);
	if (command->redir)
		heredoc = ft_heredoc(command->redir, command);
	fork_id = fork();
	++len_processes;
	if (fork_id == 0)
		ft_child(command, fd, red_pipe, *env);
	++len_processes;
	ft_redir_in(command, fd, red_pipe, heredoc);
	if (!command->pipe.out)
		retrn = ft_process_setup(fd, red_pipe, &len_processes);
	ft_free_all(command);
	ft_close_pipe(fd, *command);
	return (retrn);
}

int	ft_pipe_setting(int fd[2][2], int red_fd[2], t_cmd *command)
{
	if (command->redir)
		pipe(red_fd);
	if (command->pipe.in == 1)
	{	
		fd[1][0] = dup(fd[0][0]);
		fd[1][1] = dup(fd[0][1]);
		close(fd[0][0]);
		fd[0][0] = -1;
		close(fd[0][1]);
		fd[0][1] = -1;
	}
	if(command->pipe.out == 1)
	{
		pipe(fd[0]);
	}
	return (1);
}

int	minishell(t_cmd *command, char ***env, int fd[2][2], int red_fd[2])
{
	int	execution_status;

	command->free = NULL;
	if (command)
	{
		if (command->argum && !ft_strncmp(command->argum[0], "exit", ft_strlen(command->argum[0])))
			exit(0);
		ft_pipe_setting(fd, red_fd, command);
		execution_status = ft_execute_command(command, &(*env), fd, red_fd);
		if (execution_status == -1)
			return (0);
	}
	return (1);
}
