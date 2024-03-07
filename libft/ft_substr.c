/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcalabre & mfabbric <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:39:24 by pcalabre &        #+#    #+#             */
/*   Updated: 2024/02/28 18:39:26 by pcalabre &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	strlen;

	if (!s)
		return (0);
	strlen = ft_strlen(s);
	if (strlen < start)
		return (malloc(sizeof(char) * 1));
	if (strlen - start < len)
		len = strlen - start;
	dst = malloc(sizeof(char) * len + 1);
	if (!dst)
		return (0);
	ft_strlcpy(dst, &s[start], len + 1);
	return (dst);
}
