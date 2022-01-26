/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconchit <aconchit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 02:53:26 by aconchit          #+#    #+#             */
/*   Updated: 2022/01/26 01:07:01 by aconchit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	index;

	index = 0;
	while (s[index])
		index++;
	return (index);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	index;

	index = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[index] != '\0' && index < size - 1)
	{
		dst[index] = src[index];
		index++;
	}
	dst[index] = '\0';
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	index;
	size_t	dst_size;
	size_t	src_size;

	index = 0;
	dst_size = ft_strlen(dst);
	src_size = ft_strlen(src);
	if (dstsize == 0)
		return (src_size);
	if (dstsize < dst_size)
		return (dstsize + src_size);
	while (src[index] && dstsize > (dst_size + index))
	{
		dst[dst_size + index] = src[index];
		index++;
	}
	if (dstsize == (dst_size + index) && index > 0)
		dst[dst_size + index - 1] = '\0';
	else if (*dst)
		dst[dst_size + index] = '\0';
	return (dst_size + src_size);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size;
	char	*str;
	int		index;

	if (!s1 || !s2)
		return (NULL);
	index = 0;
	size = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, size + 1);
	return (str);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (n);
	while (*s1 && *s1 == *s2 && n - 1 > 0)
	{
		++s1;
		++s2;
		--n;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		++s1;
		++s2;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char	*ft_strdup(const char *s1)
{
	char	*cpy;
	char	*temp;
	int		index;

	temp = (char *)s1;
	index = 0;
	cpy = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!cpy)
		return (NULL);
	while (temp[index])
	{
		cpy[index] = temp[index];
		index++;
	}
	cpy[index] = '\0';
	return (cpy);
}