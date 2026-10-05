/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 08:25:45 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/05 09:06:47 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <yaml-cpp/yaml.h>
# include "config/WorldConfig.hpp"

// - PARSING -
bool parse_file_for_gui(const YAML::Node& root, WorldConfig& world);
