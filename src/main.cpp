/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 11:28:25 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/26 10:14:43 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <yaml-cpp/yaml.h>

# include "server/manager/GasterManager.hpp"
# include "server/CommandHandler.hpp"
# include "server/TCPServer.hpp"
# include "server/TCP_event.hpp"
# include "config/config.hpp"
# include "config/config_messages.h"
# include "server.h"
# include "utils.h"
# include "parser.h"


int main() {
	// Check if world data file is valid or exist.
	YAML::Node root = load_file(DATA_PATH);
	if (root.IsNull()) {
		print_error(LOAD_FILE_FAILED);
		return EXIT_FAILURE;
	}
	// Parsing of the world data.
	WorldConfig world_data;
	if (!parse_file(root, world_data)) {
		std::cerr << INVALID_DATA;
		return 1;
	 }

	// Create the manager.
	GasterManager gaster(world_data);

	CommandHandler	cmd_handler(gaster);

	TCPEvent	evt_handler(gaster);

	// Create the server.
	TCPServer server(SERVER_PORT, cmd_handler, evt_handler);
	std::cout << SERVER_LISTENING_PORT << SERVER_PORT << "...\n";
	std::cout << SERVER_LISTENING_MSG;
	server.run();

	return 0;
}
