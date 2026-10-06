/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GasterManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 14:52:27 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/05 15:05:52 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "config/WorldConfig.hpp"

class GasterManager {
	private:
		WorldConfig _world_data;

	public:
		// Constructor
		GasterManager(WorldConfig& world_data);
		// Destructor
		virtual ~GasterManager() = default;

	// DEBUG
	void debug_print_structure_data(bool show_gui_data = false);
};
