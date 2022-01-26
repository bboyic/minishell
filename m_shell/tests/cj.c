#include "../minishell.h"

int	main(void)
{
	char	*s1 = "qwert";
	char	*s2 = "yuiop";
	char	*s3;

	s3 = ft_chrjoin(s1, *s2);
	s2++;
	while (*s2)
	{
		s3 = ft_chrjoin(s3, *s2);
		printf("%s\n", s3);
		s2++;
	}
	return (0);
}
