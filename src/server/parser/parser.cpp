/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 23:35:41 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/30 13:44:16 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cctype>
# include <string>

# include "yaml-cpp/yaml.h"
# include "config/Enums.hpp"
# include "config/WorldConfig.hpp"
# include "parser.h"
# include "utils.h"

LocationConfig parse_locationConfig(const std::string& loc_id, const YAML::Node& node, std::unordered_set<std::string>& knows_locations);
ItemConfig parse_itemConfig(const std::string& item_id, const YAML::Node& node, std::unordered_set<std::string>& knows_items);
EntityConfig parse_entityConfig(const std::string& entity_id, const YAML::Node& node, std::unordered_set<std::string>& knows_entities);
QuestConfig parse_questConfig(const std::string& quest_id, const YAML::Node& node);
Direction convert_direction(const std::string& direction_str);
ItemType convert_itemType(const std::string& itemtype_str);
EnemyType convert_enemyType(const std::string& enemytype_str);
QuestStage convert_questStage(const std::string& quest_stage_str);
ValidDialogueKey convert_DialogueKey(const std::string& dialogue_key_str);
void check_global_data_validation(const std::string& name, const std::string& desc, const std::string& id);
void check_int(int value, const std::string& id);
bool is_numbered_key(const std::string& key, const std::string& prefix);
void check_locations_data(const WorldConfig& world, std::unordered_set<std::string>& knows_locations, std::unordered_set<std::string>& knows_items, std::unordered_set<std::string>& knows_entities);
std::string direction_to_string(Direction dir);

// --- PARSER (public) ---
// Validate each data and construct the global world structure.
bool parse_file(const YAML::Node& root, WorldConfig& world) {
	std::unordered_set<std::string> knows_locations; // used to check if a location exist
	std::unordered_set<std::string> knows_items; // used to check if a item exist
	std::unordered_set<std::string> knows_entities; // used to check if a entity exist
	try {
		// Check LOCATIONS
		if (root["world"] && root["world"]["locations"] && root["world"]["locations"].IsMap()) {
			for (const auto& entry : root["world"]["locations"]) {
				std::string loc_id = entry.first.as<std::string>();
				world.locations[loc_id] = parse_locationConfig(loc_id, entry.second, knows_locations);
			}
			if (7 > knows_locations.size()) {
				throw std::runtime_error("You need to have a least 8 different locations.");
			}
		}
		else {
			throw std::runtime_error("Missing locations. Did you forget? 😱");
		}

		// Check ITEMS
		if (root["items"] && root["items"].IsMap()) {
			for (const auto& entry : root["items"]) {
				std::string item_id = entry.first.as<std::string>();
				world.items[item_id] = parse_itemConfig(item_id, entry.second, knows_items);
			}
		}
		else {
			throw std::runtime_error("Missing items. Did you forget? 😱");
		}

		// Check ENTITIES
		if (root["entities"] && root["entities"].IsMap()) {
			for (const auto& entry : root["entities"]) {
				std::string entity_id = entry.first.as<std::string>();
				world.entities[entity_id] = parse_entityConfig(entity_id, entry.second, knows_entities);
			}
		}
		else {
			throw std::runtime_error("Missing entities. Did you forget? 😱");
		}

		// Check QUESTS
		if (root["quests"] && root["quests"].IsMap()) {
			for (const auto& entry : root["quests"]) {
				std::string quest_id = entry.first.as<std::string>();
				world.quests[quest_id] = parse_questConfig(quest_id, entry.second);
			}
		}
		else {
			throw std::runtime_error("Missing quests. Did you forget? 😱");
		}

		// Check if all data are valid
		check_locations_data(world, knows_locations, knows_items, knows_entities);
		// Check numbers of quests
		if (world.quests.size() < 3)
			throw std::runtime_error("You need to have a least 3 quests. Only " + std::to_string(world.quests.size() ) + " found.");
		// Check if quests are valid in the dialogue stage
		for (const auto& [entity_id, entity] : world.entities) {
			for (const auto& stage : entity.dialogue_stage) {
				if (!stage.quest_id.empty()) {
					const auto& quest_id = world.quests.find(stage.quest_id);
					if (quest_id == world.quests.end()) {
						throw std::runtime_error("Invalid quest id for dialogue stage of entity \"" + entity_id +
							"\" (" + stage.quest_id + ").");
					}
				}
			}
		}
	}
	catch (const std::exception& e) {
		print_error(std::string("PARSING FAILED!\n") + e.what());
		return false;
	}

	print_success("World Data loaded!");

	return true;
}

// Parsing for the locations part.
LocationConfig parse_locationConfig(
	const std::string& loc_id, const YAML::Node& node, std::unordered_set<std::string>& knows_locations) {
	LocationConfig config;

	knows_locations.insert(loc_id); // added to the set to check later

	// Get name and description and check
	config.name = getValue<std::string>(node, "name", "");
	config.description = getValue<std::string>(node, "description", "");
	check_global_data_validation(config.name, config.description, loc_id);

	// Checks the directions
	if (node["exits"] && node["exits"].IsMap()) {
		for (const auto& entry : node["exits"]) {
			Direction dir = convert_direction(entry.first.as<std::string>());
			config.exits[dir] = entry.second.as<std::string>();
		}
	}

	// Add the spawns and items vector even if they don't exists
	config.spawns = getValue<std::vector<std::string>>(node, "spawns", {});
	config.items = getValue<std::vector<std::string>>(node, "items", {});

	// Add the special bool (default to false)
	config.special = getValue<bool>(node, "special", false);

	return config;
}

// Parsing for the items part.
ItemConfig parse_itemConfig(
	const std::string& item_id, const YAML::Node& node, std::unordered_set<std::string>& knows_items) {
	ItemConfig config;

	knows_items.insert(item_id); // added to the set to check later

	config.name = getValue<std::string>(node, "name", "");
	config.description = getValue<std::string>(node, "description", "");
	check_global_data_validation(config.name, config.description, item_id);

	// Check the type of the item and add it
	config.type = convert_itemType(getValue<std::string>(node, "type", ""));
	if (config.type == ItemType::UNKNOWN) {
		throw std::runtime_error(item_id + " missing type for this item. Use: WEAPON, KEY or CONSUMABLE.");
	}

	config.damage = getValue<int>(node, "damage", 0);
	check_int(config.damage, item_id);
	config.hp = getValue<int>(node, "hp", 0);
	check_int(config.hp, item_id);
	return config;
}

// Parsing for the entities part.
EntityConfig parse_entityConfig(
	const std::string& entity_id, const YAML::Node& node, std::unordered_set<std::string>& knows_entities) {
	EntityConfig	config;

	knows_entities.insert(entity_id); // added to the set to check later

	config.name = getValue<std::string>(node, "name", "");
	config.description = getValue<std::string>(node, "description", "");
	check_global_data_validation(config.name, config.description, entity_id);

	if (node["dialogue"] && node["dialogue"].IsMap()) {
		for (const auto& entry : node["dialogue"]) {
			std::string dial_key = entry.first.as<std::string>();
			if (!entry.second.IsScalar()) {
				print_warning("Dialogue not scalar for \"" + entity_id + " \" and key:\"" + dial_key + "\"");
				continue;
			}

			// check if dialogue is a valid key
			if (convert_DialogueKey(dial_key) == ValidDialogueKey::UNKNOWN) {
				throw std::runtime_error("invalid dialogue key \"" + dial_key + "\" for entity \"" + entity_id + "\".");
			}

			config.dialogue[dial_key] = entry.second.as<std::string>();
		}
	}

	// Check dialogue stages
	if (node["talk_stages"] && node["talk_stages"].IsSequence()) {
		for (const auto& entry : node["talk_stages"]) {
			// if entry not a dict
			if (!entry.IsMap()) {
				throw std::runtime_error("invalid dialogue stage for entity \"" + entity_id + "\" : invalid = not a map");
			}

			DialogueStage config_dialogue;
			config_dialogue.last_stage = getValue<int>(entry, "last_stage", 0);
			// if last stage value in negative.
			if (config_dialogue.last_stage <= 0) {
				throw std::runtime_error("invalid dialogue stage for entity \"" + entity_id + "\" : invalid = "
					+ std::to_string(config_dialogue.last_stage) + ".");
			}
			// if next stage value is lower than the previous one.
			if (!config.dialogue_stage.empty() && config_dialogue.last_stage <= config.dialogue_stage.back().last_stage) {
				throw std::runtime_error("invalid dialogue stage for entity \"" + entity_id + "\" : invalid = "
					+ std::to_string(config_dialogue.last_stage) + " must be greater than previous stage "
					+ std::to_string(config.dialogue_stage.back().last_stage) + ".");
			}
			// if dialogue is not starting with "talk_"
			auto it = config.dialogue.find("talk_" + std::to_string(config_dialogue.last_stage));
			if (it == config.dialogue.end()) {
				throw std::runtime_error("invalid dialogue stage for entity \"" + entity_id + "\" : invalid = missing dialogue key: " + std::to_string(config_dialogue.last_stage));
			}
			config_dialogue.quest_id = getValue<std::string>(entry, "wait_quest", "");
			config_dialogue.condition = convert_questStage(getValue<std::string>(entry, "wait_for", ""));
			// if condition is not "COMPLETED" or "HAVE"
			if (!config_dialogue.quest_id.empty() && config_dialogue.condition == QuestStage::UNKNOWN) {
				throw std::runtime_error("invalid dialogue stage for entity \"" + entity_id + "\" : invalid = invalid condition (valid are \"completed\" or \"have\").");
			}
			config.dialogue_stage.push_back(config_dialogue);
		}
	}

	config.type = convert_enemyType(getValue<std::string>(node, "type", ""));
	if (config.type == EnemyType::UNKNOWN) {
		throw std::runtime_error(entity_id + " missing type for this item. Use: ENEMY, BOSS, NPC or SHOP.");
	}

	config.hp = getValue<int>(node, "hp", 100);
	check_int(config.hp, entity_id);
	return config;
}

QuestConfig parse_questConfig(
	const std::string& quest_id, const YAML::Node& node) {
	QuestConfig config;

	config.name = getValue<std::string>(node, "name", "");
	config.description = getValue<std::string>(node, "description", "");
	check_global_data_validation(config.name, config.description, quest_id);

	config.spawn_with_quest = getValue<bool>(node, "spawn_with_quest", false);

	return config;
}

// --- CONVERTER ---
// Convert the direction in string to an enum.
Direction convert_direction(const std::string& direction_str) {
	if (direction_str == "north") return Direction::NORTH;
	if (direction_str == "south") return Direction::SOUTH;
	if (direction_str == "east")  return Direction::EAST;
	if (direction_str == "west")  return Direction::WEST;

	return Direction::UNKNOWN;
}

// Convert the item type in string to an enum.
ItemType convert_itemType(const std::string& itemtype_str) {
	if (itemtype_str == "weapon") return ItemType::WEAPON;
	if (itemtype_str == "key") return ItemType::KEY;
	if (itemtype_str == "consumable")  return ItemType::CONSUMABLE;

	return ItemType::UNKNOWN;
}

// Convert the enemy type in string to an enum.
EnemyType convert_enemyType(const std::string& enemytype_str) {
	if (enemytype_str == "enemy") return EnemyType::ENEMY;
	if (enemytype_str == "boss") return EnemyType::BOSS;
	if (enemytype_str == "npc")  return EnemyType::NPC;
	if (enemytype_str == "shop")  return EnemyType::SHOP;

	return EnemyType::UNKNOWN;
}

// Convert the quest stage in string to an enum.
QuestStage convert_questStage(const std::string& quest_stage_str) {
	if (quest_stage_str == "completed") return QuestStage::COMPLETED;
	if (quest_stage_str == "have") return QuestStage::HAVE;

	return QuestStage::UNKNOWN;
}

// Convert the dialogue key in string to an enum.
// Keys ending with "_" are numbered (talk_1, talk_2, ...). The other keys are written exactly as is.
ValidDialogueKey convert_DialogueKey(const std::string& dialogue_key_str) {
	// --- Numbered keys ---
	if (is_numbered_key(dialogue_key_str, "talk_")) return ValidDialogueKey::TALK_;
	if (is_numbered_key(dialogue_key_str, "shop_")) return ValidDialogueKey::SHOP_;
	if (is_numbered_key(dialogue_key_str, "neutral_")) return ValidDialogueKey::NEUTRAL_;
	if (is_numbered_key(dialogue_key_str, "check_")) return ValidDialogueKey::CHECK_;
	if (is_numbered_key(dialogue_key_str, "check_bow_")) return ValidDialogueKey::CHECK_BOW_;
	if (is_numbered_key(dialogue_key_str, "act_")) return ValidDialogueKey::ACT_;
	if (is_numbered_key(dialogue_key_str, "act_coldify_")) return ValidDialogueKey::ACT_COLDIFY_;
	if (is_numbered_key(dialogue_key_str, "act_warmify_")) return ValidDialogueKey::ACT_WARMIFY_;
	if (is_numbered_key(dialogue_key_str, "act_pet_")) return ValidDialogueKey::ACT_PET_;
	if (is_numbered_key(dialogue_key_str, "act_play_")) return ValidDialogueKey::ACT_PLAY_;

	// --- Shop keys ---
	if (dialogue_key_str == "no_money") return ValidDialogueKey::NO_MONEY;
	if (dialogue_key_str == "buy") return ValidDialogueKey::BUY;
	if (dialogue_key_str == "remote") return ValidDialogueKey::REMOTE;
	if (dialogue_key_str == "quit") return ValidDialogueKey::QUIT;

	// --- Fight keys ---
	if (dialogue_key_str == "encounter") return ValidDialogueKey::ENCOUNTER;
	if (dialogue_key_str == "check_default") return ValidDialogueKey::CHECK_DEFAULT;
	if (dialogue_key_str == "low_hp") return ValidDialogueKey::LOW_HP;
	if (dialogue_key_str == "spare") return ValidDialogueKey::SPARE;
	if (dialogue_key_str == "killed") return ValidDialogueKey::KILLED;
	if (dialogue_key_str == "can_spare") return ValidDialogueKey::CAN_SPARE;
	if (dialogue_key_str == "act_result_failed") return ValidDialogueKey::ACT_RESULT_FAILED;
	if (dialogue_key_str == "act_result_won") return ValidDialogueKey::ACT_RESULT_WON;
	if (dialogue_key_str == "act_ignore") return ValidDialogueKey::ACT_IGNORE;
	if (dialogue_key_str == "act_bow") return ValidDialogueKey::ACT_BOW;
	if (dialogue_key_str == "act_bow_result") return ValidDialogueKey::ACT_BOW_RESULT;
	if (dialogue_key_str == "act_check_oufit_half_warm") return ValidDialogueKey::ACT_CHECK_OUFIT_HALF_WARM;
	if (dialogue_key_str == "act_check_oufit_half_cold") return ValidDialogueKey::ACT_CHECK_OUFIT_HALF_COLD;
	if (dialogue_key_str == "act_check_oufit_nothing") return ValidDialogueKey::ACT_CHECK_OUFIT_NOTHING;
	if (dialogue_key_str == "act_check_oufit_green") return ValidDialogueKey::ACT_CHECK_OUFIT_GREEN;
	if (dialogue_key_str == "act_check_oufit_orange") return ValidDialogueKey::ACT_CHECK_OUFIT_ORANGE;
	if (dialogue_key_str == "act_check_oufit_yellow") return ValidDialogueKey::ACT_CHECK_OUFIT_YELLOW;
	if (dialogue_key_str == "act_check_oufit_red") return ValidDialogueKey::ACT_CHECK_OUFIT_RED;

	return ValidDialogueKey::UNKNOWN;
}

// --- CHECKER ---
// Checker for the name and description.
void check_global_data_validation(const std::string& name, const std::string& desc, const std::string& id) {
	if (name.empty()) {
		throw std::runtime_error(id + " name can't be empty.");
	}
	if (desc.empty()) {
		throw std::runtime_error(id + " description can't be empty.");
	}
}

// Check if the key is the prefix followed by a number only (ex: "talk_" + "12").
// Because of the number, "act_pet_1" is not seen as an "act_" key.
bool is_numbered_key(const std::string& key, const std::string& prefix) {
	if (key.size() <= prefix.size())
		return false;
	if (key.compare(0, prefix.size(), prefix) != 0)
		return false;

	for (size_t i = prefix.size(); i < key.size(); i++) {
		if (!std::isdigit(static_cast<unsigned char>(key[i])))
			return false;
	}
	return true;
}

// Check if int is positive.
void check_int(int value, const std::string& id) {
	if (0 > value) {
		throw std::runtime_error(id + " invalid integer. Need to be positive.");
	}
}

void check_locations_data(
	const WorldConfig& world,
	std::unordered_set<std::string>& knows_locations,
	std::unordered_set<std::string>& knows_items,
	std::unordered_set<std::string>& knows_entities) {

	bool	spawn_found = false;

	for (const auto& [loc_id, loc] : world.locations) {
	for (const auto& [dir, name] : loc.exits) {
		// Check if "spawn" ID is found.
		if (loc_id == "spawn") {
			spawn_found = true;
		}

		// Check if a location exist in the directions maps
		if (knows_locations.count(name) == 0) {
			throw std::runtime_error(
				loc_id + ": '" + direction_to_string(dir) + ": " + name + "' is not a valid location.");
			}
		else {
			// Check if a location in a direction as not the same name that the location id
			if (loc_id == name) {
				throw std::runtime_error(
					loc_id + ": '" + direction_to_string(dir) + ": " + name + "' is duplicated. You will broke the reality!");
				}
			}
		}

		// Check if the entity exist in the list of spawns
		for (const auto& entity : loc.spawns) {
			if (knows_entities.count(entity) == 0) {
				throw std::runtime_error(
					loc_id + ": '" + entity + "' is not a valid entity.");
			}
		}

		// Check if the item exist in the list of items
		for (const auto& item : loc.items) {
			if (knows_items.count(item) == 0) {
				throw std::runtime_error(
					loc_id + ": '" + item + "' is not a valid item.");
			}
		}
	}

	if (!spawn_found) {
		throw std::runtime_error("spawn is missing. Make sure a zone ID is named 'spawn'.");
	}
}
