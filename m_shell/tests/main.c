#include "../minishell.h"

// void	bash_run(char *str, char **envp)
// {
// 	int	pid;
// 	int	pipe_fd[2];

// 	pipe(pipe_fd);
// 	fork

// }

int	main(int argc, char **argv, char **envp)
{
	char			*str;
	DIR				*mydir;
	struct dirent	*gointo;
	int				i;
	int				tmp;
	char			**direct;
	int				flag;

	i = -1;
	flag = 0;
	str = readline("minishell ");
	printf ("str : %s\n", str);
	sleep (1);
	while (envp[++i])
		printf ("envp[%d] : %s\n", i, envp[i]);
	printf ("\n/********************************/\n\n");
	i = -1;
	while (envp[++i])
		if (ft_strnstr(envp[i], "PATH", 4))
			tmp = i;
	printf ("envp[%d] : %s\n", tmp, envp[tmp]);
	printf ("\n/********************************/\n\n");
	direct = ft_split((ft_strchr(envp[tmp], '=') + 1), ':');
	i = -1;
	while (direct[++i])
	{
		direct[i] = ft_strjoin(direct[i], "/");
		printf ("dir[%d] : %s\n", i, direct[i]);
	}
	printf ("\n/********************************/\n\n");
	i = -1;
	while (1)
	{
		mydir = opendir (direct[++i]);
		if (!mydir)
			exit(1);
		gointo = readdir(mydir);
		while (gointo)
		{
			printf ("name : %s\n", gointo->d_name);
			if (!(ft_strncmp(gointo->d_name, str, ft_strlen(str) + 1)))
			{
				flag = 1;
				break ;
			}
			gointo = readdir(mydir);
		}
		printf ("\n/********************************/\n\n");
		if (flag)
		{
			printf ("find name : %s\n", gointo->d_name);
			break ;
			sleep (1);
		}
		closedir (mydir);
		printf ("\n/********************************/\n\n");
	}
	free(str);
	return (0);
}

/*
t_arg	*gen_arg_check(t_data **sym, int mode)
{
	int		num;
	t_arg	*local;

	num = (*sym)->red_addr;
	*local = (t_arg){};
	while ((*sym)->red_addr == num && (*sym))
	{
		ft_chrjoin(local->path, (*sym)->sym);
		sym = &(*sym)->next;
	}
	local->type = (*sym)->prev->redir;
	return (local);
}

t_arg	*gen_arg_check(t_data **sym, t_cmd *tmp)
{
	int		num;
	t_arg	*local;

	num = (*sym)->args;
	*local = (t_arg){};
	while ((*sym)->args == num && (*sym))
	{
		ft_chrjoin(local->path, (*sym)->sym);
		sym = &(*sym)->next;
	}
	return (local);
}
*/