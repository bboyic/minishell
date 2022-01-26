#include "minishell.h"

int	main(void)
{
	t_data	*tmp;

	tmp = malloc(sizeof(t_data));
	printf("before : %p, %d, %d \n", tmp->prev, tmp->pipe_in_flag, tmp->double_quote);
	*tmp = (t_data){};
	printf("after : %p, %d, %d \n", tmp->prev, tmp->pipe_in_flag, tmp->double_quote);
	return (0);
}