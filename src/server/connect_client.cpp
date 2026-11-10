/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_client.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:38:51 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/10 14:07:03 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <string>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <cstring>

# include "config/config.hpp"
# include "config/config_messages.h"
# include "utils.h"

# define IP	"127.0.0.1"


int	connect_client_to_tcp(int argc, char **argv) {
	std::string	ip = IP;
	int	port = SERVER_PORT;

	if (argc >= 2)
		ip = argv[1];

	if (argc >= 3) {
		try {
			port = std::stoi(argv[2]);
		}
		catch (const std::exception& e) {
			print_error(e.what());
			return -1;
		}

		if (port != SERVER_PORT) {
			print_error(errIncorrectPort());
			return -1;
		}
	}

	// Create the socket
	int client_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (client_fd == -1) {
        print_error(ERR_FAILED_CREATE_SOCKET);
        return -1;
    }

    struct sockaddr_in serv_addr;
    std::memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(static_cast<uint16_t>(port));

    if (inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr) <= 0) {
        print_error(errInvalidIp(ip));
        close(client_fd);
        return -1;
    }

    if (connect(client_fd, reinterpret_cast<struct sockaddr*>(&serv_addr), sizeof(serv_addr)) == -1) {
        print_error(errConnectionFailed(ip, port));
        close(client_fd);
        return -1;
    }

    return client_fd;
}
