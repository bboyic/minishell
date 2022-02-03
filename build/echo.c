#include "../minishell.h"

// void	ft_putstr(char *str)
// {
// 	while (*str)
// 		write(1, str++, 1);
// }

int	ft_echo(char **av)
{
	int	flag;

	flag = 0;
	//write(2, "1\n", 2);
	while (*(++av))
	{
		if (!ft_strcmp(*av, "-n"))
			flag = 1;
		else
			ft_putstr_fd(*av, 1);
	}
	if (flag == 0)
		write (1, "\n", 1);
	return (1);
}
