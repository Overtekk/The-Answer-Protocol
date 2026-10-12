/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GasterManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 14:52:27 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/12 13:49:29 by roandrie         ###   ########.fr       */
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
	void	createRoom();
	void	createEntities();
	void	createItems();
	void	fillRoomsData();

	public :
		// --- CONSTRUCTOR ---
		GasterManager(WorldConfig& world_data);
		// --- DESTRUCTOR ---
		~GasterManager() = default;

		// --- CREATE PLAYER ---
		void	createPlayer(const std::string& player_name);

		// --- MOVEMENT ---
		bool	movePlayer(const std::string& player_name, const Direction direction);

		// --- CHECKER ---
		bool	checkIfUserExist(const std::string& username) const;

		// --- DEBUG ---
		void	debugPrintStructureData(bool show_gui_data = false);
		void	debugPrintStructureState();
		void	debugTrySimulate(bool try_move);
};
