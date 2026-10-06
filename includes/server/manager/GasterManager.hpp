/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GasterManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 14:52:27 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/06 11:32:44 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "config/WorldConfig.hpp"
# include "config/WorldState.hpp"

class GasterManager {
	private :
		WorldConfig _world_data;
		WorldState _world_state;

	// CREATE OBJECTS
	void create_room();
	void create_entities();
	void create_items();

	public :
		// Constructor
		GasterManager(WorldConfig& world_data);
		// Destructor
		virtual ~GasterManager() = default;


	// DEBUG
	void debug_print_structure_data(bool show_gui_data = false);
	void debug_print_structure_state();
};
