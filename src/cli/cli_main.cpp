/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_main.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:14:07 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/13 13:06:58 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <poll.h>
# include <csignal>
# include <iostream>
# include <string.h>

# include "server/TCPSocket.hpp"
# include "common.h"

# define MAX_BUFFER_SIZE 1024
using namespace std;

static volatile sig_atomic_t cli_quit = 0;
void on_sigint(int){
	cli_quit = 1;
}

static std::string translate(const std::string &input){
	size_t start = input.find_first_not_of(" \t\r");
	size_t end = input.find_last_not_of(" \t\r");

	if (start == string::npos)
		return "";

	return input.substr(start, end - start + 1);
}

static bool send_line(int fd, std::string line){
	line += '\n';
	size_t off = 0;

	while (off < line.size()){
		ssize_t n = send(fd, line.c_str() + off, line.size() - off, MSG_NOSIGNAL);
		if (n <= 0)
		return false;

		off += n;
	}
	return true;
}

int main(int argc, char** argv) {
	// Connect the client to the server
	int	client_fd = connect_client_to_tcp(argc, argv);
	if (client_fd == -1) {
		return 1;
	}
	// Handles the signal
	signal(SIGINT, on_sigint);

	bool connect = true, quit = false;

	TCPSocket client_socket(client_fd);
	std::string buff;
	struct pollfd fds[2] = { {STDIN_FILENO, POLLIN, 0}, {client_fd, POLLIN, 0} };
	// Loop of the client/server communication
	while (!cli_quit) {
		if (poll(fds, 2, -1) < 0){ if (cli_quit) break; continue; }

		// Checks what the server sends
		if (fds[1].revents & (POLLIN | POLLHUP)){
			char tmp[MAX_BUFFER_SIZE];
			ssize_t n = client_socket.receiveData(tmp, sizeof tmp);
			if (n <= 0){
				std::cout << "Connection closed\n";
				connect = false;
				break;
			}

			buff.append(tmp, n);
			size_t pos;
			while ((pos = buff.find('\n')) != string::npos){
				std::string line = buff.substr(0, pos);
				buff.erase(0, pos + 1);
				std::cout << "[Server] " << line << std::endl;
				if (line == "OK bye"){
					connect = false;
					goto finish;
				}
			}
		}

		// Checks what the client sends
		if (fds[0].revents & POLLIN){
			std::string cmd;
			if (!std::getline(std::cin, cmd))
			break;

			std::string line = translate(cmd);
			if (line == "QUIT")
				quit = true;

			if (!send_line(client_fd, line)){
				connect = false;
				break;
			}
		}
	}
	finish:
	if (connect && !quit)
		send_line(client_fd, "QUIT");

	close(client_fd);

	return 0;
}
