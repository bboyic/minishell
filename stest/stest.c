#include "stest.h"

void	ft_child(char *str, int fd[2], int fd2[2], char **env)
{
	int fork_id;
	char **arg;

	arg = (char **)malloc(sizeof(char *));
	arg[0] = str;
	fork_id = fork();
	if (!fork_id)
	{
		char buf[20];
		close(fd2[0]);
		dup2(fd2[1], 1);
		dup2(fd2[1], 2);
		close(fd2[1]);
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		execve("../minishell", arg, env);
		exit(0);
	}
}

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

int	start_test(char **env, char *test, char *res, int flag)
{
	int fifo[2];
	int fifo2[2];
	char buf[1000];
	pipe(fifo);
	pipe(fifo2);
	ft_child(NULL, fifo, fifo2, env);
	buf[0] = '1';
	buf[1] = '2';
	buf[2] = '\0';
	int bytes;
	close(fifo2[1]);
	dup2(fifo2[0], 0);
	close(fifo[0]);
	write(fifo[1], test, strlen(test));
	usleep(10000);
	bytes = read(0, buf, 100);
	close(fifo[1]);
	usleep(10000);
	bytes = read(0, buf, 500);
	usleep(1000);
	bytes = read(0, buf, 1000);
	buf[bytes - 1] = 0;
	close(fifo2[0]);
	if (flag)
	{
		printf("OUTPUT:\n-----------\n");
		ft_putstr(buf);
		printf("\n-----------\n");
	}
	wait(NULL);
//	printf("%s === %s\n", res, buf);
	//printf("==%d==\n", strncmp(res, buf, strlen(buf) + 1));
	if (!strncmp(res, buf, strlen(res) + 1))
		return (1);
	else
		return (0);
}

int	main(int argc, char **argv, char **env)
{
	//start_test(env, "ls", "ls");
	int flag = 0;
	if (argc > 1 && !strcmp(argv[1], "-v"))
		flag = 1;
	printf("==TEST 1==\n");
	test(env, "ls tests", "tests/src/test1", flag);
	printf("====END====\n\n");
	printf("==TEST 2==\n");
	test(env, "ls | wc -l", "tests/src/test2", flag);
	printf("====END====\n\n");
	printf("==TEST 3==\n");
	test(env, "export ONE=1 && echo $ONE", "tests/src/test3", flag);
	printf("====END====\n\n");
	printf("==TEST 4==\n");
	test(env, "yes | head", "tests/src/test4", flag);
	printf("====END====\n\n");
	printf("==TEST 5==\n");
	test(env, "yes | head | wc -l", "tests/src/test5", flag);
	printf("====END====\n\n");
	return (0);
}