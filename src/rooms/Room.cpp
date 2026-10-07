/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Room.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 11:59:13 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/06 15:49:36 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "base_class/rooms/Room.hpp"

Room::Room(
    const std::string& name, const std::string& description, const fs::path& background,
    const bool special
):
    _name(name),
    _description(description),
    _background(background),
    _special(special)
    {
        this->_exits[Direction::NORTH] = nullptr;
        this->_exits[Direction::SOUTH] = nullptr;
        this->_exits[Direction::EAST] = nullptr;
        this->_exits[Direction::WEST] = nullptr;
    }

// ============================================================================
// ===========================      NAME      =================================
// ============================================================================

std::string     Room::getName() const {
    return (this->_name);
}

bool            Room::setName(const std::string& new_name) {
    if (new_name.length() >= 3 && new_name.length() <= 20) {
		this->_name = new_name;
		return (true);
	}
	std::cout << sendObjectError("Can't modify name. Minimum 3 and maximum 20 characters.");
	return (false);
}

// ============================================================================
// ===========================      DESC      =================================
// ============================================================================

std::string     Room::getDesription() const {
    return (this->_description);
}

bool            Room::setDescription(const std::string& new_desc) {
    if (new_desc.length() >= 5 && new_desc.length() <= 50)
    {
        this->_description = new_desc;
        return (true);
    }
    std::cout << sendObjectError("Can't modify desc. Minimum 3 and maximum 20 characters.");
    return (false);
}

// ============================================================================
// ===========================      TEXTURE      ==============================
// ============================================================================

fs::path        Room::getBGTexturePath() const {
    return (this->_background);
}

// ============================================================================
// ===========================      PLAYER      ===============================
// ============================================================================

bool            Room::addPlayer(Player* player) {
    if (player == nullptr)
    {
        std::cout << this->sendObjectError("Player's pointer point to null");
        return (false);
    }

    const std::string name = player->getName();
    if (this->_players.count(name) == 1)
    {
        std::cout << this->sendObjectError("Player already in room");
        return (false);
    }
    this->_players[name] = player;
    return (true);
}

Player*         Room::popPlayer(const std::string& name) {
    if (this->_players.count(name) == 1)
    {
        Player  *player = this->_players[name];
        this->_players.erase(name);
        return (player);
    }
    std::cout << this->sendObjectError("Invalide player name key (Player not in room)");
    return (nullptr);
}

Player*         Room::getPlayer(const std::string& name) {
    if (this->_players.count(name) == 1)
        return (this->_players[name]);
    std::cout << this->sendObjectError("Invalide player name key (Player not in room)");
    return (nullptr);
}

// ============================================================================
// =============================   npc   ======================================
// ============================================================================

bool            Room::addNPC(NPC* npc) {
    if (npc == nullptr)
    {
        std::cout << this->sendObjectError("npc's pointer point to null");
        return (false);
    }

    const std::string name = npc->getName();
    if (this->_npc.count(name) == 1)
    {
        std::cout << this->sendObjectError("npc already in room");
        return (false);
    }
    this->_npc[name] = npc;
    return (true);
}

NPC*            Room::popNPC(const std::string& name) {
    if (this->_npc.count(name) == 1)
    {
        NPC  *npc = this->_npc[name];
        this->_npc.erase(name);
        return (npc);
    }
    std::cout << this->sendObjectError("Invalide npc name key (npc not in room)");
    return (nullptr);
}

NPC*            Room::getNPC(const std::string& name) {
    if (this->_npc.count(name) == 1)
        return (this->_npc[name]);
    std::cout << this->sendObjectError("Invalide npc name key (npc not in room)");
    return (nullptr);
}

// ============================================================================
// ============================      ITEMS      ===============================
// ============================================================================

bool            Room::placeItem(Item* item) {
    if (item == nullptr)
    {
        std::cout << this->sendObjectError("Item's pointer point to null");
        return (false);
    }
    ItemID  item_id = item->getID();
    if (this->_items.count(item_id) == 1)
    {
        std::cout << this->sendObjectError("Exact item already in room");
        return (false);
    }
    this->_items[item_id] = item;
    return (true);
}

Item*           Room::popItem(ItemID item_id) {
    if (this->_items.count(item_id) == 1)
    {
        Item*   item = this->_items[item_id];
        this->_items.erase(item_id);
        return (item);
    }
    std::cout << this->sendObjectError("Invalide item name key (item not in room)");
    return (nullptr);
}

Item*           Room::getItem(ItemID item_id) {
    if (this->_items.count(item_id) == 1)
        return (this->_items[item_id]);
    std::cout << this->sendObjectError("Invalide item name key (item not in room)");
    return (nullptr);
}

// ============================================================================
// ============================      ITEMS      ===============================
// ============================================================================

void            Room::setExitNorth(Room* room) {
    this->_exits[Direction::NORTH] = room;
}

void            Room::setExitSouth(Room* room) {
    this->_exits[Direction::SOUTH] = room;
}

void            Room::setExitEast(Room* room) {
    this->_exits[Direction::EAST] = room;
}

void            Room::setExitWest(Room* room) {
    this->_exits[Direction::WEST] = room;
}

void            Room::setExitUnknown(Room* room) {
    this->_exits[Direction::UNKNOWN] = room;
}

Room*           Room::getFromDirection(Direction direction) {
    return (this->_exits[direction]);
}

// ============================================================================
// =======================      Special stats      ============================
// ============================================================================
bool            Room::isSpecial() const {
    return (this->_special);
}


std::string     Room::sendObjectError(std::string error) const {
	std::ostringstream oss;
    oss << this << " object error: " << error << "\n";
    return oss.str();
}
