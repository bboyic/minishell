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
void	ft_putstr_fd(char *str, int fd)
{
	while(*str)
		write(fd, str++, 1);
}

int	ft_check_path(char *path)
{
	while (*path)
	{
		if (*path == '/')
			return (1);
		++path;
	}
	return (0);
}


char	*ft_find_command(t_cmd command)
{
	char	*path;
	char	**paths;
	char	*check_path;
	char	*arg;
	int		index;

	index = 0;
	if (!access(command.argum[0], 1))
	{
		if (!ft_check_path(command.argum[0]))
			return (NULL);
		return (command.argum[0]);
	}
	path = getenv("PATH");
	paths = ft_split(path, ':');
	arg = ft_strjoin("/", command.argum[0]);
	while (paths[index])
	{
		check_path = ft_strjoin(paths[index], arg);
		if (!access(check_path, 0))
		{
			free(paths);
			free(arg);
			return (check_path);
		}
		++index;
		free(check_path);
	}
	free(arg);
	return (NULL);
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

int	ft_redir(t_arg *redir, int mode)
{
	int		infile;
	int		outfile;
	int		byte;
	char	buf;
	int		heredoc;

	heredoc = 0;
	infile = -1;
	outfile = -1;
	while (redir)
	{
		if (redir->type == L_REDIR && mode == 1)
		{
			heredoc = 0;
			if (infile != -1)
				close(infile);
			infile = open(redir->path, O_RDONLY);
			if (infile == -1)
				return (0);
		}
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
		if (redir->type == HEREDOC && mode == 1)
			heredoc = 1;
		redir = redir->next;
	}
	byte = 1;
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
	if (heredoc)
		return (HEREDOC);
	return (1);
}

char	*ft_heredoc(t_arg *redir)
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
			while (ft_strcmp(str, redir->path))
			{
				final = ft_strjoin(final, str);
				final = ft_strjoin(final, "\n");
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
}

void	ft_child(t_cmd *command, int fd[2][2], int red_pipe[2], char **env)
{
	char	*path;

	if (command->argum)
	{
		ft_pipex(red_pipe, fd, command);
		ft_close(fd);
		ft_system(command, env);
		path = ft_find_command(*command);
		if (!path)
			exit (1);
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

	exit_status = 0;
	while (len_processes-- > 0)
	{
		wait(&status);
		if (WEXITSTATUS(status) == 1)
			exit_status = 1;
	}
	return(exit_status);
}


int	ft_execute_command(t_cmd *command, char **env, int fd[2][2], int red_pipe[2])
{
	static int	len_processes = 0;
	int			fork_id;
	int			redir_status;
	char		*heredoc;

	heredoc = NULL;
	if (command->argum && !ft_strcmp(command->argum[0], "cd"))
	{
		ft_cd(command->argum[1]);
		return (1);
	}
	if (command->redir)
		heredoc = ft_heredoc(command->redir);
	fork_id = fork();
	++len_processes;
	if (fork_id == 0)
	{
		if (command->redir)
			ft_redir(command->redir, 0);
		ft_child(command, fd, red_pipe, env);
	}
	if (fork_id)
	{
		++len_processes;
		if (fork() == 0)
		{
			if (command->redir)
			{
				close(red_pipe[0]);
				dup2(red_pipe[1], 1);
				close(red_pipe[1]);
				fd[0][1] = -1;
				redir_status = ft_redir(command->redir, 1);
				if (redir_status == HEREDOC)
				{
					ft_putstr_fd(heredoc, 1);
				}
				ft_close(fd);
			}
			exit(0);
		}
	}
	if (fork_id && !command->pipe.out)
	{
		ft_close(fd);
		close(red_pipe[0]);
		close(red_pipe[1]);
		if (ft_wait_processes(len_processes) == 0)
		{
			len_processes = 0;
			return (-1);
		}
		len_processes = 0;
	}
	ft_close_pipe(fd, *command);
	return (1);
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

int	minishell(t_cmd *command, char **env, int fd[2][2], int red_fd[2])
{
	int	execution_status;

	if (command)
	{
		if (command->argum && !ft_strncmp(command->argum[0], "exit", ft_strlen(command->argum[0])))
			exit(0);
		ft_pipe_setting(fd, red_fd, command);
		execution_status = ft_execute_command(command, env, fd, red_fd);
		if (execution_status == 1 && command->var_or == 1)
			return (1);
		if (!execution_status)
			return (0);
		if (execution_status == -1)
		{
			while (command->var_or != 1 && command->next != NULL)
				command = command->next;
		}
		command = command->next;
	}
	return (1);
}

t_cmd	*ft_newlist(char *path, int pipi, int pipo, int or, int red_type, char *red_path)
{
	t_cmd *pars;

	pars = (t_cmd *)malloc(sizeof(t_cmd));
	pars->argum = ft_split(path, ' ');
	pars->pipe.in = pipi;
	pars->pipe.out = pipo;
	pars->var_or = or;
	pars->next = NULL;
	return (pars);
}

t_cmd	*ft_add_list(t_cmd *list, char *path, int pipi, int pipo, int or, int red_type, char *red_path, t_arg *red, t_arg *heredoc)
{
	t_cmd	*new;

	if (list)
		new = list;
	else
	{
		new = ft_newlist(path, pipi, pipo, or, red_type, red_path);
		if (red)
			new->redir = red;
		return (new);
	}
	while (new->next)
		new = new->next;
	new->next = ft_newlist(path, pipi, pipo, or, red_type, red_path);
	if (red)
		new->next->redir = red;
	return (list);
}
