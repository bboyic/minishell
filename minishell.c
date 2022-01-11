/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:32:20 by aarchiba          #+#    #+#             */
/*   Updated: 2022/01/11 21:25:57 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	error_end(char *str, int flag)
{
	if (flag >= 0)
	{
		if (flag == 1)
		{
			printf ("Error: atoi/incorrect argument\n");
			exit (1);
		}
	}
}
