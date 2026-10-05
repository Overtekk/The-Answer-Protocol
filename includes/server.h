/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 12:11:19 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/05 09:46:40 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <yaml-cpp/yaml.h>
# include "config/WorldConfig.hpp"

bool load_file(const std::string& filepath, YAML::Node& root);
bool parse_file(const YAML::Node& root, WorldConfig& world);
