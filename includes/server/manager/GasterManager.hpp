/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GasterManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 14:52:27 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/10 14:14:47 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <chrono>
# include <queue>
# include <string>
# include <unordered_map>
# include <vector>

# include "base_class/entities/Entity.hpp"
# include "config/Enums.hpp"
# include "config/WorldConfig.hpp"
# include "config/WorldState.hpp"
# include "core/QuestManager.hpp"
# include "core/DialogueManager.hpp"
# include "core/CombatManager.hpp"

// Dialogue
enum class TalkStatus {OK, NOT_FOUND, NO_DIALOGUE};
struct TalkResult {
	TalkStatus	status = TalkStatus::NOT_FOUND;
	std::string	entity_name;
	std::string	text;
	bool		has_more = false;
};

// Combat
enum class CombatTurn {PLAYER, ENTITY, NONE};
inline constexpr std::chrono::milliseconds	COMBAT_CLOCK_DELAY{1000};

// A message to send to a player (the server writes it in the session of the player).
struct CombatMessage {
	std::string	player_name;
	std::string	text;
	bool		combat_over = false;
};

struct CombatProgress {
	Player*		player;
	Entity*		entity;
	CombatTurn	turn = CombatTurn::PLAYER;
	std::chrono::steady_clock::time_point	next_action_time;
	std::queue<std::string>					messages;			// messages waiting to be sent, one per delay
	CombatStatus							end_status = CombatStatus::NOTHING;	// result of the enemy action
};


// * Orchestor of the program. *
class GasterManager {
	private :
		WorldConfig	_world_data;
		WorldState	_world_state;

		QuestManager	_quest_manager;
		DialogueManager	_dialogue_manager;
		CombatManager	_combat_manager;

		std::unordered_map<std::string, CombatProgress>	_combat_lists;

	// --- CREATE OBJECTS ---
	void	createRoom();
	void	createEntities();
	void	createItems();
	void	fillRoomsData();

	std::string	createStartingWeapon(std::string& player_name);

	// --- DELETE OBJECTS ---
	void	deleteEntity(Entity* entity);

	void	respawnPlayer(Player* player);

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

		// --- CREATE PLAYER ---
		void	createPlayer(const std::string& player_name);

		// --- MOVEMENT ---
		ReturnState	movePlayer(const std::string& player_name, const Direction direction);

		// --- ITEMS MANAGEMENT ---
		const std::string	getPlayerInventory(const std::string& player_name, bool add_details) const;
		ReturnState			takeItem(const std::string& player_name, const std::string& item_name);
		ReturnState			dropItem(const std::string& player_name, const std::string& item_name);
		ReturnState			equipNewWeapon(const std::string& player_name, const std::string& item_name);
		const std::string	getItemStat(const std::string& player_name, const std::string& item_name);

		// --- DIALOGUE MANAGEMENT ---
		TalkResult			getDialogue(const std::string& player_name, const std::string& entity_id);

		// --- COMBAT MANAGEMENT ---
		std::vector<CombatMessage>	updateCombats();

		ReturnState			isEnemyType(const std::string& player_name, const std::string& entity_id);
		const std::string	initCombat(const std::string& player_name);
		const std::string	getCombatStatus(const std::string& player_name);
		const std::string	combatPlayerAttack(const std::string& player_name);
		const std::string	combatEnemyAttack(const std::string& player_name);
		CombatStatus		checkCombatStatus(const std::string& player_name);
		bool				tryFlee(const std::string& player_name);
		void				finishCombat(const std::string& player_name);
		const std::string	combatCheck(const std::string& player_name);
		CombatTurn			getCombatWhoTurn(const std::string& player_name);
		const std::string	changeCombatWhoTurn(const std::string& player_name, CombatTurn turn);

		// --- QUESTS ---
		const std::string	getPlayerQuests(const std::string& player_name) const;
		const std::string	getQuestDescription(const std::string& player_name, const std::string& quest_id) const;

		// --- CHECKER ---
		bool	checkIfUserExist(const std::string& username) const;

		// --- ADMIN ---
		ReturnState	adminKill(const std::string& player_name);
};
