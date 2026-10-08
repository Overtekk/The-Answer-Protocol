/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 15:03:04 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/08 15:09:13 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "yaml-cpp/yaml.h"
# include "utils.h"

// - Load files -
YAML::Node load_file(const std::string& filepath);

// --- TEMPLATE ---
// Safely extracts a typed value from a YAML node with fallback to defaultValue on error or missing key.
template <typename T>
T getValue(const YAML::Node& parent, const std::string& key, const T& defaultValue) {
	if (parent[key] && parent[key].IsDefined()) {
		try {
			return parent[key].as<T>();
		}
		catch (const YAML::Exception& e) {
			print_error(e.what());
			return defaultValue;
		}
	}
	return defaultValue;
}
