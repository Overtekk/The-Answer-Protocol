/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_main.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:14:07 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/12 16:51:19 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdio.h>
# include <cstdio>
# include <string.h>
# include <sys/socket.h>
# include <sys/stat.h>
# include <sys/types.h>

# include "server/TCPSocket.hpp"
# include "common.h"

# define MAX_BUFFER_SIZE 100


int main(int argc, char** argv) {
	// Connect the client to the server
	int	client_fd = connect_client_to_tcp(argc, argv);
	if (client_fd == -1) {
		return 1;
	}

	TCPSocket client_socket(client_fd);
	char r_buff[MAX_BUFFER_SIZE] = "", s_buff[MAX_BUFFER_SIZE] = "";
	while (1) {
		printf("\nClient → Server: ");
		fgets(s_buff, MAX_BUFFER_SIZE, stdin);
		client_socket.sendData(s_buff);

		if (strcmp(s_buff, "end") == 0)
		break;

		usleep(1000);

		client_socket.receiveData(r_buff, sizeof r_buff);
		std::cout << "Server → Client: " << r_buff << std::endl;

		if (strcmp(r_buff, "end") == 0)
		break;
	}

	close(client_fd);

	return 0;
}
