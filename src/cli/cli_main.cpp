/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_main.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:14:07 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/08 15:25:28 by roandrie         ###   ########.fr       */
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

	close(client_fd);

	return 0;
}
