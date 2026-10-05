/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 11:28:25 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/05 09:47:41 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "server.h"
# include "gui.h"
# include "debug.h"

int main() {
	YAML::Node root;
	if (!load_file("data/world_data.yaml", root)) {
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
