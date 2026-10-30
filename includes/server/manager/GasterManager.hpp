/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GasterManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 14:52:27 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/30 16:12:11 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <string>
# include <vector>

# include "base_class/entities/Entity.hpp"
# include "config/WorldConfig.hpp"
# include "config/WorldState.hpp"
# include "core/QuestManager.hpp"
# include "core/DialogueManager.hpp"
# include "core/CombatManager.hpp"


enum class TalkStatus { OK, NOT_FOUND, NO_DIALOGUE };
struct TalkResult {
	TalkStatus	status = TalkStatus::NOT_FOUND;
	std::string	entity_name;
	std::string	text;
	bool		has_more = false;
};


// * Orchestor of the program. *
class GasterManager {
	private :
		WorldConfig	_world_data;
		WorldState	_world_state;

		QuestManager	_quest_manager;
		DialogueManager	_dialogue_manager;
		CombatManager	_combat_manager;

	// --- CREATE OBJECTS ---
	void	createRoom();
	void	createEntities();
	void	createItems();
	void	fillRoomsData();

	// --- GETTER ---
	const Player*	getPlayer(const std::string& player_name) const;
	Player*			getPlayer(const std::string& player_name);
	const Item*		getItem(const std::string& item_name) const;
	Item*			getItem(const std::string& item_name);
	const Room*		getRoom(const std::string& room_id) const;
	Room*			getRoom(const std::string& room_id);
	const Entity*	getEntity(const std::string& entity_id) const;
	Entity*			getEntity(const std::string& entity_id);

	// --- DIALOGUES ---
	bool	isConditionMet(const Player& player, const DialogueStage& stage) const;
	int		getTalkLimit(const Player& player, const std::vector<DialogueStage>& stages) const;

	public :
		// --- CONSTRUCTOR ---
		GasterManager(WorldConfig& world_data);
		// --- DESTRUCTOR ---
		~GasterManager() = default;

		// --- GETTER ---
		const std::string	getListOfPlayers() const;
		const std::string	getRoomData(const std::string& player_name, bool add_details) const;
		const std::string	getPlayerRoom(const std::string& player_name) const;
		const std::string	getPlayerInventory(const std::string& player_name, bool add_details) const;
		const std::string	getPlayerQuests(const std::string& player_name) const;
		const std::string	getQuestDescription(const std::string& player_name, const std::string& quest_id) const;
		TalkResult			getDialogue(const std::string& player_name, const std::string& entity_id);

		// --- CREATE PLAYER ---
		void	createPlayer(const std::string& player_name);

		// --- MOVEMENT ---
		bool	movePlayer(const std::string& player_name, const Direction direction);

		// --- ITEMS MANAGEMENT ---
		bool	takeItem(const std::string& player_name, const std::string& item_name);
		bool	dropItem(const std::string& player_name, const std::string& item_name);

		// --- CHECKER ---
		bool	checkIfUserExist(const std::string& username) const;

		// --- DEBUG ---
		void	debugPrintStructureData(bool show_gui_data = false);
		void	debugPrintStructureState();
		void	debugTrySimulate(bool try_move);
};
