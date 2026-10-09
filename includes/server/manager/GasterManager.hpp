/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GasterManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 14:52:27 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/09 09:24:49 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>

# include "config/WorldConfig.hpp"
# include "config/WorldState.hpp"


// * Orchestor of the program. *
class GasterManager {
	private :
		WorldConfig	_world_data;
		WorldState	_world_state;

	// --- CREATE OBJECTS ---
	void	create_room();
	void	create_entities();
	void	create_items();

	public :
		// --- CONSTRUCTOR ---
		GasterManager(WorldConfig& world_data);
		// --- DESTRUCTOR ---
		~GasterManager() = default;

		// --- CREATE PLAYER ---
		bool	create_player(const std::string& player_name);

		// --- CHECKER ---
		bool	checkIfUserExist(const std::string& username) const;

		// --- DEBUG ---
		void	debug_print_structure_data(bool show_gui_data = false);
		void	debug_print_structure_state();
};
