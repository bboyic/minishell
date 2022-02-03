/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconchit <aconchit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 15:53:54 by aconchit          #+#    #+#             */
/*   Updated: 2022/01/26 01:07:17 by aconchit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	ft_putstr(char *str)
// {
// 	while (*str)
// 		write(1, str++, 1);
// }

int	ft_env(char **env)
{
	while (*env)
	{
		ft_putstr_fd(*(env++), 1);
		write(1, "\n", 1);
	}
	return (0);
}
