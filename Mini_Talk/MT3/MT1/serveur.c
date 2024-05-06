#include "minitalk.h"
/*
void	ft_handle_signal(int signum, siginfo_t *info, void *context)
{
	static unsigned char	character = 0;
	static int				bit_count = 0;
	static pid_t			client_pid = 0;

	(void)context;
	if (client_pid != info->si_pid)
	{
		bit_count = 0;
		character = 0;
	}
	client_pid = info->si_pid;
	character = character << 1;
	if (signum == SIGUSR1)
		character = character | 1;
	bit_count++;
	if (bit_count == 8)
	{
		write(1, &character, 1);
		bit_count = 0;
		character = 0;
	}
	kill(client_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server PID: %d\n", getpid());
	sa.sa_sigaction = &ft_handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		;
	return (0);
}

#Version pasquelafleurici

#include "ft_printf.h"

void	bit_handler(int bit)
{
	int	i;

	struct si	g_msg;
	i = 0;
	g_msg.c += ((bit & 1) << g_msg.i);
	g_msg.i++;
	if (g_msg.i == 7)
	{
		ft_printf("%c", g_msg.c);
		if (!g_msg.c)
			ft_printf("\n");
		g_msg.c = 0;
		g_msg.i = 0;
	}
}

int	main(void)
{
	ft_printf("Welcome To Pasquale's Server!\n");
	ft_printf("My Server PID is: %d\n", getpid());
	while (1)
	{
		signal(SIGUSR2, bit_handler);
		signal(SIGUSR1, bit_handler);
		pause();
	}
	return (0);
}

#Version hanshazairi fonctionel mais sans unicode
#include <signal.h>
#include <unistd.h>
#include "libft.h"

static void	action(int sig, siginfo_t *info, void *context)
{
	static int				i = 0;
	static pid_t			client_pid = 0;
	static unsigned char	c = 0;

	(void)context;
	if (!client_pid)
		client_pid = info->si_pid;
	c |= (sig == SIGUSR2);
	if (++i == 8)
	{
		i = 0;
		if (!c)
		{
			kill(client_pid, SIGUSR2);
			client_pid = 0;
			return ;
		}
		ft_putchar_fd(c, 1);
		c = 0;
		kill(client_pid, SIGUSR1);
	}
	else
		c <<= 1;
}

int	main(void)
{
	struct sigaction	s_sigaction;

	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	s_sigaction.sa_sigaction = action;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	while (1)
		pause();
	return (0);
}


//Version eschirni <eschirni@student.42.fr
extern char	*g_client;

char	*ft_appendC(char *start, char c)
{
	size_t	i;
	char	*tmp;

	tmp = malloc(ft_strlen(start) + 2);
	if (tmp == NULL)
		return (NULL);
	i = 0;
	while (start[i] != '\0')
	{
		tmp[i] = start[i];
		i++;
	}
	tmp[i] = c;
	tmp[i + 1] = '\0';
	free(start);
	return(tmp);
}

// resets the global variable (25 line problem)
static void	ft_del_global(void)
{
	free(g_client);
	g_client = NULL;
}

// converts binary to ascii or unicode
// returns the result as an integer
// if it's not just for comparison it prints the character
static int	ft_convert(char *s, int b_write)
{
	int				pow;
	int				c;
	size_t			i;

	pow = 1;
	c = 0;
	i = ft_strlen(s) - 1;
	while (i + 1 != 0)
	{
		c += pow * (s[i] - '0');
		pow *= 2;
		i--;
	}
	if (b_write == 1)
	{
		write(1, &c, 1);
		return (0);
	}
	return (c);
}

// reads every bit and appends it to bits
// if its a 8 bit ascii char or a 24 bit unicode char it converts it
// the result gets printed and the server sends the client an ack
static void	ft_confirm(int sig)
{
	static char	*bits;
	static int	bitcount;

	bitcount++;
	if (bits == NULL)
	{
		bits = ft_strdup("");
		bitcount = 1;
	}
	if (sig == SIGUSR2)
		bits = ft_appendC(bits, '0');
	else
		bits = ft_appendC(bits, '1');
	if ((bitcount == 8 && ft_convert(bits, 0) < 255) || bitcount == 24)
	{
		if (ft_convert(bits, 0) == 0 && bitcount != 24)
			ft_del_global();
		else
		{
			ft_convert(bits, 1);
			kill(ft_atoi(g_client), SIGUSR1);
		}
		free(bits);
		bits = NULL;
	}
}

// safes all bits in a string and conerts every byte to a char
// the char will get appended to the client variable (PID)
static void	ft_get_pid(int sig)
{
	static char	*bits;
	static int	bitcount;

	bitcount++;
	if (bits == NULL)
	{
		bits = ft_strdup("");
		bitcount = 1;
	}
	if (sig == SIGUSR2)
		bits = ft_appendC(bits, '0');
	else
		bits = ft_appendC(bits, '1');
	if (bitcount == 8)
	{
		g_client = ft_appendC(g_client, ft_convert(bits, 0));
		free(bits);
		bits = NULL;
	}
}

// if it has not the clinet PID it takes 8 bytes the client PID
// otherwise it will decode the binary to ascii and print it
int	main(void)
{
	ft_printf("Server PID: %u\n", getpid());
	while (1 == 1)
	{
		if (g_client == NULL)
		{
			g_client = ft_strdup("");
			while (ft_strlen(g_client) < 7)
			{
				signal(SIGUSR1, ft_get_pid);
				signal(SIGUSR2, ft_get_pid);
				pause();
			}
		}
		signal(SIGUSR1, ft_confirm);
		signal(SIGUSR2, ft_confirm);
		pause();
	}
	return (0);
}
*/
//Version lgaudin <lgaudin@student.42malaga.com>

#define END_TRANSMISSION '\0'
/*
 * @brief    Checks if the signal is SIGUSR1. If it is, it will
 * assign 1 to the LSB. Else, it will assign 0 (actually it simply
 * won't modify it).
 *
 * Example:
 * 00101100   current_char
 * 00000001   result of (sigsent == SIGUSR1)
 * --------
 * 00101101   result stored in message after the bitwise OR operation
 *
 * It will then increment the bit index.
 * If it is 8, it means that the char has been fully transmitted.
 * It will then print it and reset the bit index and the current char.
 * Else, it will shift the current char to the left by 1.
 *
 * @param    signal    SIGUSR1 or SIGUSR2
 */
void	handle_signal(int signal, siginfo_t *info, void *context)
{
	static unsigned char	current_char;
	static int				bit_index;

	(void)context;
	current_char |= (signal == SIGUSR1);
	bit_index++;
	if (bit_index == 8)
	{
		if (current_char == END_TRANSMISSION)
			ft_printf("\n");
		else
			ft_printf("%c", current_char);
		bit_index = 0;
		current_char = 0;
	}
	else
		current_char <<= 1;
	if (signal == SIGUSR1)
		kill(info->si_pid, SIGUSR1);
	else if (signal == SIGUSR2)
		kill(info->si_pid, SIGUSR2);
}

/**
 * @brief    Prints its program's PID and calls the signal handlers.
 */
int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	printf("%d\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
