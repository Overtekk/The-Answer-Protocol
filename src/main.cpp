/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 11:28:25 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/01 12:28:50 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "server.h"

int main() {
	std::cout << "Hello World, i'm the server!\n";

	if (!load_file("data/world_data.yaml")) {
		return EXIT_FAILURE;
	}

	std::cout << "Goodbye!\n";

	return 0;
}
