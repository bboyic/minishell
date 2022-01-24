/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconchit <aconchit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 01:30:12 by aconchit          #+#    #+#             */
/*   Updated: 2022/01/25 02:13:51 by aconchit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*==DICTIONARY FOR ENV==*/
typedef struct s_env
{
	struct s_env	*next;
	char			*key;
	char			*value;
	
}	t_env;

/*==DICTIONARY CREATOR==*/
t_env	*ft_new_list(char *data)
{
	char	**split;
	t_env	*list;

	if (!data)	
		return (NULL);
	split = NULL;
	list = (t_env *)malloc(sizeof(t_env));
	if (!list)
		return (NULL);
	list->next = NULL;
	if (data)
		split = ft_split(data, '=');
	if (!split)
		return (NULL);
	list->key = split[0];
	list->value = split[1];
	free(split);
	return (list);
}

/*==CONVERT **char env TO DICTIONARY ENV==*/
t_env	*ft_env_to_list(char **env)
{
	t_env	*env_list;
	t_env	*res;

	env_list = ft_new_list(*env);
	if (!env_list)
		return(NULL);
	res = env_list;
	while (env)
	{
		env_list->next = ft_new_list(*env);
		if (!env_list->next)
			return (res);
		env_list = env_list->next;
		env++;
	}
	return (res);
}

/*==TEST MAIN==*/
int	main(int argc, char **argv, char **env)
{
	t_env	*list_env;
	t_env	*temp;

	list_env = ft_env_to_list(env);
	while (list_env)
	{
		printf("%s = %s\n", list_env->key, list_env->value);
		temp = list_env;
		list_env = list_env->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
	return (0);
}