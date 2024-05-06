/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfemeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:58:23 by anfemeni          #+#    #+#             */
/*   Updated: 2024/02/16 16:00:09 by anfemeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>

int		ft_print_char(char s);
int		ft_print_str(const char *s);
int		ft_print_arg(char spe, va_list args);
int		ft_print_ptr(unsigned long long n);
int		ft_print_nb(int n);
int		ft_print_uns(unsigned int n);
int		ft_printf(const char *format, ...);
size_t	ft_x_len(long long n);
size_t	ft_intlen(long int n);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *str, size_t n);
void	*ft_memset(void *str, int c, size_t n);
int		ft_print_hex(unsigned long long n, char spe);
#endif
