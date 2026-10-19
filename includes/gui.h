/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 08:25:45 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/19 10:34:44 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <queue>

# include <yaml-cpp/yaml.h>
# include "config/WorldConfig.hpp"
# include "config/LoadedAssets.hpp"


// - PARSING -
bool    parse_file_for_gui(std::queue<YAML::Node>& nodes_list, WorldConfig& world);
bool	LoadAssets(WorldConfig& config, LoadedAssets& assets);
void	UnloadAssets(LoadedAssets& assets);
