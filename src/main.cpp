/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 11:28:25 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/06 09:53:29 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "server.h"
# include "utils.h"
# include "debug.h"
# include "server/manager/GasterManager.hpp"

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

	 GasterManager gaster = GasterManager(world_data);
	 gaster.debug_print_structure_state();

	return 0;
}
