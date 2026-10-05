/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Room.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 11:59:13 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/05 12:13:25 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "base_class/rooms/Room.hpp"

Room::Room(
    const std::string& name, const std::string& description, const fs::path& background,
    const bool save_point, const bool special
):
    _name(name),
    _description(description),
    _background(background),
    _save_point(save_point),
    _special(special)
    {
    }

// ============================================================================
// ===========================      NAME      =================================
// ============================================================================
std::string Room::getName() const {
    return (this->_name);
}

bool        Room::setName(const std::string& new_name) {
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
std::string Room::getDesription() const {
    return (this->_description);
}

bool        Room::setDescription(const std::string& new_desc) {
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
fs::path    Room::getBGTexturePath() const {
    return (this->_background);
}

// ============================================================================
// ===========================      PLAYER      ===============================
// ============================================================================

bool        Room::addPlayer(Player* player) {
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

Player*     Room::popPlayer(const std::string& name) {
    if (this->_players.count(name) == 1)
    {
        Player  *player = this->_players[name];
        this->_players.erase(player->getName());
        return (player);
    }
    std::cout << this->sendObjectError("Invalide player name key (Player not in room)");
    return (nullptr);
}

Player*     Room::getplayer(const std::string& name) {
    if (this->_players.count(name) == 1)
        return (this->_players[name]);
    std::cout << this->sendObjectError("Invalide player name key (Player not in room)");
    return (nullptr);
}

// ============================================================================
// =======================      Special stats      ============================
// ============================================================================
bool        Room::isSavePoint() const {
    return (this->_save_point);
}

bool        Room::isSpecial() const {
    return (this->_special);
}


std::string Room::sendObjectError(std::string error) const {
	std::ostringstream oss;
    oss << this << " object error: " << error << "\n";
    return oss.str();
}