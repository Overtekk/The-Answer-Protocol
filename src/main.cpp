/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 11:28:25 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/05 13:36:04 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "server.h"
# include "utils.h"
# include "debug.h"

int main() {
	YAML::Node root = load_file("data/test.yaml");
	if (root.IsNull()) {
		print_error("Failed to load file.");
		return EXIT_FAILURE;
	}
	WorldConfig world_data;
	if (!parse_file(root, world_data)) {
		std::cerr << "\n❌ Server aborting: invalid world data configuration.\n";
		return 1;
	 }

	 debug_print_structure(world_data);

	return 0;
}
