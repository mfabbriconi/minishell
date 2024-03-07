/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcalabre & mfabbric <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:38:51 by pcalabre &        #+#    #+#             */
/*   Updated: 2024/02/28 18:38:53 by pcalabre &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	int		slen;

	slen = ft_strlen(s) + 1;
	str = malloc(sizeof(char) * slen);
	if (str == 0)
		return (0);
	ft_strlcpy(str, s, slen);
	return (str);
}
