#include "minitalk.h"
/*
int	g_confirm_flag = 0;

void	ft_resp_handler(int signum)
{
	g_confirm_flag = 1;
	(void)signum;
}

void	ft_send_bit(int pid, int bit)
{
	int	signal;

	if (bit == 1)
		signal = SIGUSR1;
	else
		signal = SIGUSR2;
	if (kill(pid, signal) == -1)
	{
		ft_putstr_fd("Error", 2);
		exit(EXIT_FAILURE);
	}
	while (!g_confirm_flag)
		;
	g_confirm_flag = 0;
}

void	ft_send_char(int pid, unsigned char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		ft_send_bit(pid, (c >> i) & 1);
		usleep(400);
		i--;
	}
}

void	ft_send_string(int pid, const char *str)
{
	while (*str)
		ft_send_char(pid, *str++);
	ft_send_char(pid, '\0');
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
	{
		ft_putstr_fd("Usage: ./client [PID] [string]\n", 2);
		exit(EXIT_FAILURE);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		ft_putstr_fd("Invalid PID\n", 2);
		exit(EXIT_FAILURE);
	}
	signal(SIGUSR2, ft_resp_handler);
	ft_send_string(pid, argv[2]);
	return (0);
}

#Version pas quuelafleuricic
#include "ft_printf.h"

void	send_bit(int pid, char *str, size_t len)
{
	int		shift;
	size_t	i;

	i = 0;
	while (i <= len)
	{
		shift = 0;
		while (shift < 7)
		{
			if ((str[i] >> shift) & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			shift++;
			usleep(300);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*str;

	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		str = argv[2];
		send_bit(pid, str, ft_strlen(str));
	}
	else
		ft_printf("\nYOU EITHER LEFT IT BLANK OR ARE DOING MORE THAN 1 WORD\n\n");
}


//Version hanshazairi bof
#include <signal.h>
#include <unistd.h>
#include "libft.h"


static void	action(int sig)
{
	static int	received = 0;

	if (sig == SIGUSR1)
		++received;
	else
	{
		ft_putnbr_fd(received, 1);
		ft_putchar_fd('\n', 1);
		exit(0);
	}
}

static void	mt_kill(int pid, char *str)
{
	int		i;
	char	c;

	while (*str)
	{
		i = 8;
		c = *str++;
		while (i--)
		{
			if (c >> i & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(100);
		}
	}
	i = 8;
	while (i--)
	{
		kill(pid, SIGUSR1);
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	if (argc != 3 || !ft_strlen(argv[2]))
		return (1);
	ft_putstr_fd("Sent    : ", 1);
	ft_putnbr_fd(ft_strlen(argv[2]), 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("Received: ", 1);
	signal(SIGUSR1, action);
	signal(SIGUSR2, action);
	mt_kill(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}

// Version eschirni <eschirni@student.42.fr

#include "minitalk.h"

int		ft_atoi(const char *str)
{
	int neg;
	int i;
	int num;

	i = 0;
	neg = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * neg);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;
	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *str)
{
	size_t	i;
	char	*tmp;

	i = 0;
	if (!str)
		return (NULL);
	tmp = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	if (tmp == NULL )
		return (NULL);
	while (str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

extern char	*g_client;

// always called when the server sends a signal
// appends a to the global so it can compare the length in the main
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
	return (tmp);
}

static void	ft_ack(int sig)
{
	char	*temp;

	if (sig == SIGUSR1)
	{
		temp = ft_appendC(g_client, 'a');
		g_client = temp;
	}
}

// sends the binary message to the server
// when it has sent 8 it checks for a server response
// waits so the signals won't get ignored
static void	ft_send_msg(int pid, char *s)
{
	size_t	i;

	i = 1;
	while (s[i - 1] != '\0')
	{
		if (s[i - 1] == '1')
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		if (i % 8 == 0)
		{
			signal(SIGUSR1, ft_ack);
		}
		i++;
		usleep(160);
	}
}

// converts the string to binary
// starts from the end of the string with conversion
// puts the binary number at the end of ret
// unsigned char so it can handle unicode too
static char	*ft_to_bit(char *s, size_t i, size_t j)
{
	char	*ret;
	int		c;
	int		bytes;

	i = ft_strlen(s);
	ret = ft_calloc(i * 8 + 1, sizeof(unsigned char));
	if (ret == NULL)
		return (NULL);
	while (i + 1 != 0)
	{
		c = (unsigned char) s[i - 1];
		bytes = 8;
		while (bytes > 0)
		{
			if (c % 2 == 1)
				ret[ft_strlen(s) * 8 - j - 1] = '1';
			else
				ret[ft_strlen(s) * 8 - j - 1] = '0';
			c /= 2;
			j++;
			bytes--;
		}
		i--;
	}
	return (ret);
}

// sends his own PID to the server
// if the PID less than 8 chars then send 01 till its 8
static void	ft_send_pid(int pid, int i)
{
	char	*client_pid;
	char	*client_bin;

	client_pid = ft_itoa(getpid());
	client_bin = ft_to_bit(client_pid, 0, 0);
	free(client_pid);
	while (client_bin[i] != '\0')
	{
		if (client_bin[i] == '1')
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i++;
		usleep(80);
	}
	while (i < 56)
	{
		kill(pid, SIGUSR2);
		usleep(80);
		kill(pid, SIGUSR1);
		usleep(80);
		i += 2;
	}
	free(client_bin);
}

// Converts his own PID to binary and sends it to the server
// Converts the message to binary and sends it to the the server
// sends 00000000 after eveything has been sent
// compares the number of chars to the number of server responses
int	main(int argc, char **argv)
{
	int		pid;
	char	*bits;

	if (argc != 3)
	{
		ft_printf("wrong number of arguments\n");
		return (0);
	}
	pid = ft_atoi(argv[1]);
	bits = ft_to_bit(argv[2], 0, 0);
	if (bits == NULL)
	{
		ft_printf("allocation error\n");
		return (0);
	}
	g_client = ft_strdup("");
	ft_send_pid(pid, 0);
	ft_send_msg(pid, bits);
	ft_send_msg(pid, "00000000");
	if (ft_strlen(argv[2]) == ft_strlen(g_client))
		ft_printf("Message arrived without problems\n");
	else
		ft_printf("Message error!\n");
	free(bits);
	free(g_client);
}
*/
//Version lgaudin <lgaudin@student.42malaga.com>

/**
 * @brief    Sends 8 signals to the provided PID to transmit the
 * provided character bit by bit.
 * It starts from the MSB and progressively goes to the LSB.
 *
 * It sends SIGUSR1 if the bit is 1, SIGUSR2 if it is 0.
 *
 * @param    pid       server's PID
 * @param    character character to transmit
 */
void	send_signal(int pid, unsigned char character)
{
	int				i;
	unsigned char	temp_char;

	i = 8;
	temp_char = character;
	while (i > 0)
	{
		i--;
		temp_char = character >> i;
		if (temp_char % 2 == 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(420);
	}
}

/**
 * @brief    Handles the signals sent back by the server and prints
 * the corresponding information.
 *
 * @param    signal    The signal sent back by the server.
 */
void	handle_read_receipt(int signal)
{
	if (signal == SIGUSR1)
		ft_printf("Received bit 1\n");
	else if (signal == SIGUSR2)
		ft_printf("Received bit 0\n");
}

/**
 * @brief    Sends a message to the server character by character.
 *
 * @param    argc
 * @param    argv
 */
int	main(int argc, char *argv[])
{
	pid_t		server_pid;
	const char	*message;
	int			i;

	signal(SIGUSR1, handle_read_receipt);
	signal(SIGUSR2, handle_read_receipt);
	if (argc != 3)
	{
		ft_printf("Usage: %s <pid> <message>\n", argv[0]);
		exit(0);
	}
	server_pid = ft_atoi(argv[1]);
	message = argv[2];
	i = 0;
	while (message[i])
		send_signal(server_pid, message[i++]);
	send_signal(server_pid, '\0');
	return (0);
}

