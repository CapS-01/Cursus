/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfemeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:02:47 by anfemeni          #+#    #+#             */
/*   Updated: 2024/05/06 16:02:50 by anfemeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
# include "minitalk.h"

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
void handle_read_receipt(int signal)
{
	if (signal == SIGUSR1)
        return ;
		//ft_printf("Received bit 1\n");
	else if (signal == SIGUSR2)
		return ;
        //ft_printf("Received bit 0\n");

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


	if (argc != 3)
	{
		ft_printf("Usage: %s <pid> <message>\n", argv[0]);
		exit(0);
	}
    signal(SIGUSR1, handle_read_receipt);
	signal(SIGUSR2, handle_read_receipt);
	server_pid = ft_atoi(argv[1]);
	message = argv[2];
	i = 0;
	while (message[i])
		send_signal(server_pid, message[i++]);
	send_signal(server_pid, '\0');
	return (0);
}