/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfemeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:54:37 by anfemeni          #+#    #+#             */
/*   Updated: 2024/05/06 15:38:34 by anfemeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <errno.h>

t_stack	*ft_sub_process(char **argv)
{
	t_stack	*a;
	char	**tmp;
	int		i;
	int		j;

	a = NULL;
	i = 0;
	j = 0;
	if (is_correct_input(argv) != 0)
	{	write(1, "Error\n", 6);
		// ft_freestr(argv);
		// ft_freestr(argv);
		exit(1);
	}// 	ft_freestr(tmp);
		tmp = ft_split(argv[1], ' ');
	while (tmp[i])
	{
		j = ft_atoi(tmp[i]);
		if (errno == 1)
		{
			ft_freestr(tmp);
			free(tmp);
			exit_error(&a, NULL);
			errno = 0;
		}
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
			errno = 1;
		i = i * 10 + (*str - 48);
		str++;
	}
	if ((mod * i) > 2147483647 || (mod * i) < -2147483648)
		errno = 1;
	return (mod * i);
}
