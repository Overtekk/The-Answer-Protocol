/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 12:11:19 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/09 09:57:42 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <string>

# include <yaml-cpp/yaml.h>
# include "config/WorldConfig.hpp"


bool	parse_file(const YAML::Node& root, WorldConfig& world);
