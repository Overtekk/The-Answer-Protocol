/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_main.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:14:07 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/09 13:49:16 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>

# include "common.h"


int main(int argc, char** argv) {
	// Connect the client to the server
	int	client_fd = connect_client_to_tcp(argc, argv);
	if (client_fd == -1) {
		return 1;
	}

	// todo: while(1) and get std::cin of client and sent to socket. Read what server send.
	// while(1){
	// 	std::cin;
	// }

	close(client_fd);

	return 0;
}
