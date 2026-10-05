/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 08:25:45 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/05 11:58:02 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <queue>
# include <yaml-cpp/yaml.h>
# include "raylib.h"
# include "config/WorldConfig.hpp"

// - PARSING -
bool parse_file_for_gui(std::queue<YAML::Node>& nodes_list, WorldConfig& world);
