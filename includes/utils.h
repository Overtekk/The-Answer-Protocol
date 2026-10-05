/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 12:14:57 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/05 11:04:07 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <queue>
# include <yaml-cpp/yaml.h>
# include "config/WorldConfig.hpp"

# define pass (void)0

// - Print -
void print_error(const std::string& error_msg);
void print_success(const std::string& msg);
void print_warning(const std::string& warning_msg);
void print_log(const std::string& log_msg);

// - Enum convert -
std::string direction_to_string(Direction dir);
std::string enemy_type_to_string(EnemyType type);
std::string item_type_to_string(ItemType type);

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

// Extract a element from a queue, pop it and return the value
template <typename T>
T pop_front(std::queue<T>& q) {
    T val = std::move(q.front());
    q.pop();
    return val;
}
