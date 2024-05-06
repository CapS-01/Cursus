#ifndef MINITALK_H
# define MINITALK_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include "libft.h"
# include "ft_printf.h"
/*
// Client
void	ft_send_bit(int pid, int bit);
void	ft_send_char(int pid, unsigned char c);
void	ft_send_string(int pid, const char *str);
void	ft_resp_handler(int signum);

// Server
void	ft_handle_signal(int signum, siginfo_t *info, void *context);
*/
char			*g_client;
#endif
