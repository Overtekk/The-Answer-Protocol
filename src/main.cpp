/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 11:28:25 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/01 14:48:27 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <yaml-cpp/yaml.h>
# include "server.h"
# include "config/WorldConfig.hpp"

int main() {
	WorldConfig world_data;
	YAML::Node root;
	if (!load_file("data/world_data.yaml", root)) {
		return EXIT_FAILURE;
	}
	parse_file(root, world_data);

	return 0;
}
