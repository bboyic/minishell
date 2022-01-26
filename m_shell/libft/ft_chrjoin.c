/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 20:49:32 by aarchiba          #+#    #+#             */
/*   Updated: 2022/01/23 18:02:13 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_chrjoin(char const *s1, char s2)
{
	char	*tmp;
	long	i;

	i = -1;
	if (s1)
	{
		tmp = malloc(sizeof(char) * ((ft_strlen(s1) + 2)));
		if (!tmp)
			return (NULL);
		while (s1[++i])
			tmp[i] = s1[i];
		tmp[i] = s2;
		tmp[i + 1] = '\0';
		return (tmp);
	}
	else
	{
		tmp = malloc(sizeof(char) * 2);
		tmp[0] = s2;
		tmp[1] = '\0';
		return (tmp);
	}
	return (NULL);
}
