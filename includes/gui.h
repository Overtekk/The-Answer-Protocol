/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 08:25:45 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/20 17:11:51 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "raylib.h"
# include <queue>
# include <yaml-cpp/yaml.h>
# include "config/WorldConfig.hpp"
# include "config/LoadedAssets.hpp"


// - PARSING -
bool    parse_file_for_gui(std::queue<YAML::Node>& nodes_list, WorldConfig& world);
bool	LoadAssets(WorldConfig& config, LoadedAssets& assets);
void	UnloadAssets(LoadedAssets& assets);

bool checkCollison(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);
Vector2 clamp(const Vector2 &original, float max_x, float min_x, float max_y, float min_y);
