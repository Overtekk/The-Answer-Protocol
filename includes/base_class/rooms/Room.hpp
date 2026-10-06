/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Room.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 11:59:17 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/06 13:16:31 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <string>
# include <filesystem>
# include <unordered_map>
# include "base_class/items/Item.hpp"
# include "base_class/entities/Player.hpp"
# include "base_class/entities/Entity.hpp"
# include "base_class/entities/NPC.hpp"
# include "config/Enums.hpp"

namespace fs = std::filesystem;

// * ABSTRACT CLASS *
class Room {
    private :
        std::string                                     _name;
        std::string                                     _description;
        fs::path                                        _background;
        std::unordered_map<ItemID, Item*>               _items;
        std::unordered_map<std::string, Player*>        _players;
        std::unordered_map<std::string, NPC*>           _npc;
        //std::unordered_map<Direction, std::string>   	_exits;
        bool                                            _special;

    public:
        // --- CONSTRUCTOR ---
        Room(
			const std::string& name, const std::string& description, const fs::path& background,
			const bool _special);
		// --- DESTRUCTOR ---
        virtual ~Room() = default;

        // Name
        std::string             getName() const;
        bool                    setName(const std::string& new_name);

        // Description
        std::string             getDesription() const;
        bool                    setDescription(const std::string& new_desc);

        // Players
        bool                    addPlayer(Player* player);
        Player*                 popPlayer(const std::string& name);
        Player*                 getPlayer(const std::string& name);

        // NPC
        bool                    addNPC(NPC* npc);
        NPC*                    popNPC(const std::string& name);
        NPC*                    getNPC(const std::string& name);

        // Items
        bool                    placeItem(Item* item);
        Item*                   popItem(ItemID item_id);
        Item*                   getItem(ItemID item_id);

        // Special stats
        bool                    isSpecial() const;

        // Texture
        fs::path                getBGTexturePath() const;

        // Error
        std::string sendObjectError(std::string error) const;
};
