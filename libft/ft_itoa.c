/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcalabre & mfabbric <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:38:25 by pcalabre &        #+#    #+#             */
/*   Updated: 2024/02/28 18:38:28 by pcalabre &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(size_t n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	ft_set_tab(char *str, int n, int i, int neg)
{
	str[i] = 0;
	while (i > 0)
	{
		i--;
		str[i] = n % 10 + 48;
		n /= 10;
	}
	if (neg == 1)
		str[0] = 45;
}

char	*ft_itoa(int n)
{
	char	*str;
	int		nbrlen;
	int		neg;

	neg = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		n *= -1;
		neg = 1;
		nbrlen = ft_nbrlen(n) + 1;
	}
	else
		nbrlen = ft_nbrlen(n);
	str = malloc(sizeof(char) * (nbrlen + 1));
	if (str == 0)
		return (0);
	else
		ft_set_tab(str, n, nbrlen, neg);
	return (str);
}
