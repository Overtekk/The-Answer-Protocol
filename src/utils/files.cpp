/* *********************************************************************** */
/*                                                                         */
/*                                                     :::      ::::::::   */
/* files.cpp                                         :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+     */
/* By: roandrie <roandrie@student.42lehavre.fr   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+           */
/* Created: 2026/10/05 10:23:50 by roandrie        #+#    #+#              */
/* Updated: 2026/10/05 13:26:04 by roandrie        ###   ########.fr       */
/*                                                                         */
/* *********************************************************************** */

# include "yaml-cpp/yaml.h"
# include "config/WorldConfig.hpp"
# include "utils.h"

// Try to load a YAML file.
YAML::Node load_file(const std::string& filepath) {
	YAML::Node root;
	try {
		root = YAML::LoadFile(filepath);
		if (root.IsNull()) {
			print_error("File is empty.\n");
		}
	}
	catch (const YAML::Exception& e) {
		print_error(e.what());
		return root;
	}
	return root;
}
