/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 11:28:25 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/08 09:47:53 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <csignal>
# include <cstdlib>
# include <system_error>

# include "server.h"
# include "utils.h"
# include "debug.h"
# include "server/manager/GasterManager.hpp"
# include "server/TCPServer.hpp"

// A signal handler must be a plain function (not a member, not a lambda with captures).
// It does the bare minimum: set a flag. The server loop notices it within 100 ms (poll timeout).
static void handleSignal(int) { TCPServer::requestStop(); }


int main() {
	YAML::Node root = load_file("data/world_data.yaml");
	if (root.IsNull()) {
		print_error("Failed to load file.");
		return EXIT_FAILURE;
	}
	WorldConfig world_data;
	if (!parse_file(root, world_data)) {
		std::cerr << "\n❌ Server aborting: invalid world data configuration.\n";
		return 1;
	 }

	// Installed before run(): a Ctrl+C at any later point is caught.
	struct sigaction sa{};
	sa.sa_handler = handleSignal;
	sigemptyset(&sa.sa_mask);
	// No SA_RESTART on purpose: poll() must return EINTR so the loop can re-check the flag.
	sigaction(SIGINT, &sa, nullptr);
	sigaction(SIGTERM, &sa, nullptr);

	try {
		TCPServer server(4242);
		print_success("Server listening on port 4242...");
		server.run();
	}
	catch (const std::exception& e) {   // system_error derives from exception
		print_error(e.what());
		return EXIT_FAILURE;
	}
	return 0;
}
