/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 11:23:33 by aconchit          #+#    #+#             */
/*   Updated: 2022/02/03 06:00:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_sort(char **env)
{
	while (*env && env[1])
	{
		if (ft_strcmp(*env, env[1]) > 0)
			return (0);
		else if (*env)
			++env;
	}
	return (1);
}

int	ft_max(char **env)
{
	int	index;

	index = 0;
	while (env[index])
		++index;
	return (index);	
}

int	ft_print_sort_env(char **env)
{
	int		max;
	char	**sort_env;
	char	*temp;
	int		index;
	int		sort_index;

	index = 0;
	sort_index = 0;
	max = ft_max(env);
	sort_env = (char **)malloc(sizeof(char) * (max + 1));
	while (sort_index < max)
	{
		sort_env[sort_index] = env[sort_index];
		++sort_index;
	}
	sort_index = 0;
	while (sort_index < max - 1)
	{
		index = 0;
		while (index < max - 1)
		{
			if (ft_strcmp(sort_env[sort_index], sort_env[index]) < 0)
			{
				temp = sort_env[sort_index];
				sort_env[sort_index] = sort_env[index];
				sort_env[index] = temp;
			}
			++index;
		}
		++sort_index;
	}
	sort_env[max - 1] = NULL;
	while (*sort_env)
		printf("%s\n", *(sort_env++));
	return (1);
}

char	**ft_export(char **env, char **arg)
{
	char	**new_env;
	int		max;
	int		index;
	int		env_index;

	
	max = ft_max(env);
	if (!*arg)
	{
		ft_print_sort_env(env);
		return (env);
	}
	index = 0;
	env_index = 0;
	while (arg[index])
	{
		max++;
		index++;
	}
	index = 0;
	new_env = (char **)malloc(sizeof(char *) * (max + ft_max(arg)));
	if (!new_env)
		return (NULL);
	while (*arg)
		new_env[index++] = ft_strdup(*(arg++));
	while (env[index])
		new_env[index++] = ft_strdup(env[env_index++]);
	new_env[index] = NULL;
	return (new_env);
}

int	ft_check_arg(char *str, char **arg)
{
	char	*check;
	int		index;

	index = 0;
	check = (char *)malloc(sizeof(char) * ft_strlen(str));
	if (!check)
		return (-1);
	while (*str != '=' && *str)
		check[index++] = *(str++);
	check[index] = '\0';
	while (*arg)
	{
		if (!ft_strcmp(*arg, check))
		{
			free(check);
			return (1);
		}
		++arg;
	}
	free(check);
	return (0);
}

char **ft_unset(char **env, char **arg)
{
	char	**new_env;
	int		max;
	int		index;

	if (!*arg)
		return (env);
	index = 0;
	max = ft_max(env);
	new_env = (char **)malloc(sizeof(char *) * (max + 1));
	if (!new_env)
		return (NULL);
	new_env[max] = NULL;
	while (*env)
	{
		if (ft_check_arg(*env, arg))
			++env;
		else if (*env)
		{
			new_env[index++] = ft_strdup(*env);
			++env;
		}
	}
	new_env[index] = NULL;
	return (new_env);
}

// int	main(int argc, char **argv, char **env)
// {
// 	char **av;
// 	char *a[] = {"a", "b", "c", NULL};
// 	char *b[] = {NULL};
// 	char **new_env;
// 	int index;

// 	index = 0;
// 	av = (char **)malloc(sizeof(char *) * argc);
// 	while (argc-- > 0)
// 		av[index++] = ft_strdup(*(argv++));
// 	av[index] = NULL;
// 	new_env = ft_export(env, ++av);
// 	ft_export(new_env, b);
// 	printf("\n\n\n\n\n\n\n\n");
// 	new_env = ft_unset(new_env, a);
// 	ft_export(new_env, b);
// 	//free(env);
// 	return (0);
// }