/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 11:28:25 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/09 09:03:37 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>

# include <yaml-cpp/yaml.h>
# include "server/manager/GasterManager.hpp"
# include "server/CommandHandler.hpp"
# include "server/TCPServer.hpp"
# include "server.h"
# include "config/config.hpp"
# include "utils.h"
# include "parser.h"
# include "debug.h"


int main() {
	// Check if world data file is valid or exist.
	YAML::Node root = load_file("data/world_data.yaml");
	if (root.IsNull()) {
		print_error("Failed to load file.");
		return EXIT_FAILURE;
	}
	// Parsing of the world data.
	WorldConfig world_data;
	if (!parse_file(root, world_data)) {
		std::cerr << "\n❌ Server aborting: invalid world data configuration.\n";
		return 1;
	 }

	// Create the manager.
	 GasterManager gaster(world_data);

	 CommandHandler	cmd_handler(gaster);

	 // Create the server.
	 TCPServer server(SERVER_PORT, cmd_handler);
	 std::cout << "Server listening on port " << SERVER_PORT << "...\n";
	 server.run();

	//  gaster.debug_print_structure_state();

	return 0;
}
