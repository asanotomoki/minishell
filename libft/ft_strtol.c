/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanotomoki <asanotomoki@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 04:17:38 by asanotomoki       #+#    #+#             */
/*   Updated: 2022/10/29 07:15:52 by asanotomoki      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isbase(int c, int base)
{
	if (base == 0)
		return (c == '0');
	else if (1 <= base && base <= 10)
		return ('0' <= c && c <= '0' + base - 1);
	else if (11 <= base && base <= 36)
		return (ft_isdigit(c) || ('a' <= c && c <= 'a' + base - 11));
	else
		return (-1);
}

int	charmap(int c, int base)
{
	if (!ft_isbase(c, base))
		return (-1);
	if (ft_isdigit(c))
		return (c - '0');
	else if ('a' <= c && c <= 'z')
		return (c - 'a' + 10);
	else if ('A' <= c && c <= 'Z')
		return (c - 'A' + 10);
	return (-1);
}

int	set_base(const char **str, int base)
{
	char	*ptr;

	ptr = (char *)*str;
	if (base == 0 || ((base == 8 || base == 16) && *ptr == '0'))
	{
		if ((base == 0 || base == 8) && ft_isbase(ptr[1], 8))
		{
			ptr++;
			base = 8;
		}
		else if ((base == 0 || base == 16) && \
			(ptr[1] == 'x' || ptr[1] == 'X') && ft_isbase(ptr[2], 16))
		{
			ptr += 2;
			base = 16;
		}
	}
	*str = ptr;
	return (base);
}

long	set_endptr(long res, char ***endptr, const char *str)
{
	if (*endptr)
		**endptr = (char *)str;
	return (res);
}

long	ft_strtol(const char *str, char **endptr, int base)
{
	long	res;
	int		sign;
	int		set_c;

	if (base < 0 || 36 < base)
		return (set_endptr(0, &endptr, str));
	while (ft_isspace(*str))
		str++;
	base = set_base(&str, base);
	sign = -1;
	if ((*str == '+' || *str == '-') && ft_isbase(str[1], base))
		sign = -(44 - *str++);
	res = 0;
	while (*str)
	{
		set_c = charmap(*str, base);
		if (set_c == -1)
			break ;
		res = (res * base) - set_c;
		str++;
	}
	return (set_endptr(res * sign, &endptr, str));
}
