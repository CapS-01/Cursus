/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfemeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:54:37 by anfemeni          #+#    #+#             */
/*   Updated: 2024/04/29 11:03:48 by anfemeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*ft_sub_process(char **av)
{
	t_stack	*a;
	char	**tmp;
	int		i;
	int		j;

	a = NULL;
	i = 0;
	j = 0;
	tmp = ft_split(av[1], ' ');
	while (tmp[i])
	{
		j = ft_atoi(tmp[i]);
		stack_add_bottom(&a, stack_new(j));
		i++;
	}
	ft_freestr(tmp);
	free(tmp);
	return (a);
}

t_stack	*ft_parse_args_quoted(char **argv)
{
	t_stack	*stack_a;
	char	**tmp;

	stack_a = NULL;
	tmp = ft_split(argv[1], 32);
	list_args(tmp, &stack_a);
	ft_freestr(tmp);
	free(tmp);
	return (stack_a);
}

void	list_args(char **argv, t_stack **stack_a)
{
	long	i;

	i = 1;
	while (argv[i] != NULL)
	{
		stack_add_bottom(stack_a, stack_new(ft_atoi(argv[i])));
		i++;
	}
}

int	ft_atoi(const char *str)
{
	int		mod;
	long	i;

	i = 0;
	mod = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\f' \
			|| *str == '\v' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			mod *= -1;
		str++;
	}
	while (*str)
	{
		if (!is_digit(*str))
			exit_error(NULL, NULL);
		i = i * 10 + (*str - 48);
		str++;
	}
	if ((mod * i) > 2147483647 || (mod * i) < -2147483648)
		exit_error(NULL, NULL);
	return (mod * i);
}
