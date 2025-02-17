/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoalen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 02:05:54 by ibertran          #+#    #+#             */
/*   Updated: 2024/10/27 18:33:43 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_itoalen(int n)
{
	int	i;

	i = 1;
	if (n < 0)
		i++;
	while (n / 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	ft_itoalen_base(int n, char *base)
{
	int	i;
	int	base_len;

	base_len = strlen(base);
	i = 1;
	if (n < 0)
		i++;
	while (n / base_len)
	{
		n /= base_len;
		i++;
	}
	return (i);
}

int	ft_uitoalen_base(unsigned int n, char *base)
{
	int	i;
	int	base_len;

	base_len = strlen(base);
	i = 1;
	while (n / base_len)
	{
		n /= base_len;
		i++;
	}
	return (i);
}

int	ft_ulltoalen_base(unsigned long long nbr, char *base)
{
	int	i;
	int	base_len;

	base_len = strlen(base);
	i = 1;
	while (nbr / base_len)
	{
		nbr /= base_len;
		i++;
	}
	return (i);
}
