#include "minishell.h"

void	wash_pizduk_tut(char **envp, int *pipe_fd, sem_t *sem)
{
	char	*str = "zooazea";
	int		i = -1;

	//printf("PID pizduk_tut: %d\n", getpid());
	close(pipe_fd[0]);
	while (str[++i])
	{
		sem_wait(sem);
		write(pipe_fd[1], &str[i], 1);
		sem_post(sem);
		usleep(100);
	}
	close(pipe_fd[1]);
	exit(16);
}

void	wash_pizduk_tam(char **envp, int *pipe_fd, sem_t *sem)
{
	char	*str = "drv abl";
	int		i = -1;

	//printf("PID pizduk_tam: %d\n", getpid());
	usleep(1);
	close(pipe_fd[0]);
	while (str[++i])
	{
		sem_wait(sem);
		write(pipe_fd[1], &str[i], 1);
		sem_post(sem);
		usleep(100);
	}
	close(pipe_fd[1]);
	exit(16);
}

int	main(int argc, char **argv, char **envp)
{
	int		pid;
	int		pid1;
	int		pid2;
	int		ret;
	int		pipe_fd[2];
	char	c;
	sem_t	*family;

	sem_unlink("family");
	family = sem_open("family", O_CREAT, S_IRWXU, 1);
	pid = getpid();
	printf ("PID process: %d\n", pid);
	pipe(pipe_fd);
	pid1 = fork();
	if (pid1 == 0)
		wash_pizduk_tut(envp, pipe_fd, family);
	pid2 = fork();
	if (pid2 == 0)
		wash_pizduk_tam(envp, pipe_fd, family);
	close(pipe_fd[1]);
	while (1)
	{
		ret = read(pipe_fd[0], &c, 1);
		if (ret <= 0)
			break ;
		write(1, &c, 1);
	}
	write(1, "\n", 1);
	close(pipe_fd[0]);
	waitpid(pid2, &ret, 0);
	printf ("bteak : %d\n", ret);
}
